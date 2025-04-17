#include "hal/gpio.h"

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/dt-bindings/gpio/gpio.h>
#include <zephyr/pm/device.h>

#include "hal/detail/dt.h"
#include "util/compiler.h"
#include "util/debug.h"
#include "util/stdinc.h"

#define __MORT_GPIO_ENSURE_PIN_NUMBER_VALID(__pin)                                                 \
    MORT_RETURN_LOGE_IF(                                                                           \
        (__pin) >= MORT_GPIO_PIN_MAX, -EINVAL, "GPIO error: Invalid GPIO pin number: %d", (__pin))

#define __MORT_GPIO_CTX_PTR(__pin) &__S_GPIO_CONTEXTS[pin]

typedef struct
{
    const struct gpio_dt_spec *spec;
    gpio_flags_t               flags;
    struct gpio_callback       callback;
    mort_gpio_int_handler_cb   handler;
} __mort_gpio_ctx_t;

// -----------------------------------------------------------------------------

/// @brief Convert a GPIO event to Zephyr GPIO interrupt config flag(s).
/// @param[in] event The event to convert.
/// @return The Zephyr GPIO interrupt config flag(s).
/// @note "event" must be a valid mort_gpio_event_e value.
static unsigned int __mort_gpio_event_to_zephyr(mort_gpio_event_e event);

/// @brief The global GPIO interrupt callback function.
/// @param[in] port The GPIO port on which the interrupt occurred.
/// @param[in] cb The GPIO callback associated with the interrupt.
/// @param[in] pins The GPIO pin(s) on which the interrupt occurred.
static void
__mort_gpio_on_interrupt(const struct device *port, struct gpio_callback *cb, uint32_t pins);

// -----------------------------------------------------------------------------

static __mort_gpio_ctx_t __S_GPIO_CONTEXTS[MORT_GPIO_PIN_MAX] = {
    [MORT_GPIO_PIN_DBG_LED]    = {&MORT_DT_SPEC_GPIO_DBG_LED, GPIO_OUTPUT_INACTIVE},
    [MORT_GPIO_PIN_NEC_IN]     = {&MORT_DT_SPEC_GPIO_NEC_IN, GPIO_INPUT},
    [MORT_GPIO_PIN_MOTOR_AIN1] = {&MORT_DT_SPEC_GPIO_MOTOR_AIN1, GPIO_OUTPUT_INACTIVE},
    [MORT_GPIO_PIN_MOTOR_AIN2] = {&MORT_DT_SPEC_GPIO_MOTOR_AIN2, GPIO_OUTPUT_INACTIVE},
    [MORT_GPIO_PIN_MOTOR_BIN1] = {&MORT_DT_SPEC_GPIO_MOTOR_BIN1, GPIO_OUTPUT_INACTIVE},
    [MORT_GPIO_PIN_MOTOR_BIN2] = {&MORT_DT_SPEC_GPIO_MOTOR_BIN2, GPIO_OUTPUT_INACTIVE},
    [MORT_GPIO_PIN_MOTOR_STBY] = {&MORT_DT_SPEC_GPIO_MOTOR_STBY, GPIO_OUTPUT_INACTIVE},
};

// -----------------------------------------------------------------------------

int mort_gpio_init(void)
{
    for (mort_gpio_pin_e pin = 0; pin < MORT_GPIO_PIN_MAX; pin++)
    {
        const __mort_gpio_ctx_t *ctx = __MORT_GPIO_CTX_PTR(pin);

        if (!ctx->spec)
        {
            continue;
        }

        bool ok = gpio_is_ready_dt(ctx->spec);
        MORT_RETURN_LOGE_IF(!ok, -EIO, "GPIO error: GPIO pin %d is not ready", pin);

        int ec = gpio_pin_configure_dt(ctx->spec, ctx->flags);
        MORT_RETURN_LOGE_IF(ec < 0, -EIO, "GPIO error: Failed to configure GPIO pin %d", pin);
    }

    pm_device_wakeup_enable(MORT_GPIOA, true);

    return 0;
}

int mort_gpio_set(mort_gpio_pin_e pin, int state)
{
    __MORT_GPIO_ENSURE_PIN_NUMBER_VALID(pin);

    const __mort_gpio_ctx_t *ctx = __MORT_GPIO_CTX_PTR(pin);

    int ec = gpio_pin_set_dt(ctx->spec, state);
    MORT_RETURN_LOGE_IF(ec < 0, -EIO, "GPIO error: Failed to set GPIO pin %d to %d", pin, state);

    return 0;
}

int mort_gpio_toggle(mort_gpio_pin_e pin)
{
    __MORT_GPIO_ENSURE_PIN_NUMBER_VALID(pin);

    const __mort_gpio_ctx_t *ctx = __MORT_GPIO_CTX_PTR(pin);

    int ec = gpio_pin_toggle_dt(ctx->spec);
    MORT_RETURN_LOGE_IF(ec < 0, -EIO, "GPIO error: Failed to toggle GPIO pin %d", pin);

    return 0;
}

int mort_gpio_attach_interrupt(
    mort_gpio_pin_e pin, mort_gpio_event_e event, mort_gpio_int_handler_cb cb)
{
    __MORT_GPIO_ENSURE_PIN_NUMBER_VALID(pin);
    MORT_RETURN_LOGE_IF(event >= MORT_GPIO_EVT_MAX, -EINVAL, "GPIO error: Invalid event %d", event);

    __mort_gpio_ctx_t *ctx = __MORT_GPIO_CTX_PTR(pin);
    int                ec  = 0;

    if (!cb)
    {
        ec = gpio_pin_interrupt_configure_dt(ctx->spec, GPIO_INT_MODE_DISABLED);
        MORT_RETURN_LOGE_IF(
            ec < 0, -EIO, "GPIO error: Failed to disable GPIO interrupt on pin %d", pin);

        ec = gpio_remove_callback_dt(ctx->spec, &ctx->callback);
        MORT_RETURN_LOGE_IF(
            ec < 0, -EIO, "GPIO error: Failed to remove GPIO callback on pin %d", pin);
        memset(&ctx->callback, 0, sizeof(ctx->callback));

        ctx->handler = NULL;

        return 0;
    }

    unsigned int flags = __mort_gpio_event_to_zephyr(event);

    ctx->handler = cb;

    gpio_init_callback(&ctx->callback, __mort_gpio_on_interrupt, BIT(ctx->spec->pin));
    ec = gpio_add_callback_dt(ctx->spec, &ctx->callback);
    MORT_RETURN_LOGE_IF(ec < 0, -EIO, "GPIO error: Failed to add GPIO callback on pin %d", pin);

    ec = gpio_pin_interrupt_configure_dt(ctx->spec, flags);
    MORT_RETURN_LOGE_IF(
        ec < 0, -EIO, "GPIO error: Failed to configure GPIO interrupt on pin %d", pin);

    return 0;
}

static unsigned int __mort_gpio_event_to_zephyr(mort_gpio_event_e event)
{
    static unsigned int __S_ZEPHYR_EVENT_LUT[MORT_GPIO_EVT_MAX] = {
        [MORT_GPIO_EVT_RISING_EDGE]  = GPIO_INT_EDGE_RISING,
        [MORT_GPIO_EVT_FALLING_EDGE] = GPIO_INT_EDGE_FALLING,
    };

    return __S_ZEPHYR_EVENT_LUT[event];
}

static void
__mort_gpio_on_interrupt(const struct device *port, struct gpio_callback *cb, uint32_t pins)
{
    MORT_UNUSED(port);
    MORT_UNUSED(cb);

    for (mort_gpio_pin_e pin = 0; pin < MORT_GPIO_PIN_MAX; pin++)
    {
        __mort_gpio_ctx_t *ctx = __MORT_GPIO_CTX_PTR(pin);

        if ((pins & BIT(ctx->spec->pin)) && ctx->handler)
        {
            ctx->handler();
        }
    }
}
