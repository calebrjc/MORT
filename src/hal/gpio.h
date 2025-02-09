#pragma once

// TODO(Caleb):
// - Consider how one would reconfigure a specific GPIO pin (probably not needed for MORT).

/// @brief GPIO pin numbers.
typedef enum
{
    MORT_GPIO_PIN_DBG_LED = 0x00,
    MORT_GPIO_PIN_NEC_IN  = 0x01,
    MORT_GPIO_PIN_MAX,
} mort_gpio_pin_e;

typedef enum
{
    MORT_GPIO_EVT_NONE = 0x00,
    MORT_GPIO_EVT_RISING_EDGE,
    MORT_GPIO_EVT_FALLING_EDGE,
	MORT_GPIO_EVT_MAX,
} mort_gpio_event_e;

/// @brief GPIO interrupt handler callback.
typedef void (*mort_gpio_int_handler_cb)(void);

/// @brief Initialize all GPIO pins.
/// @return 0 if successful, or -EIO if an error occured.
int mort_gpio_init(void);

/// @brief Set a GPIO pin to a given state.
/// @param pin The GPIO pin.
/// @param state The state to set the GPIO to (1 or 0).
/// @return 0 if successful, or an error code.
/// @retval -EINVAL if the GPIO pin is invalid.
/// @retval -EIO if a GPIO error occured.
int mort_gpio_set(mort_gpio_pin_e pin, int state);

/// @brief Toggle the state of a GPIO pin.
/// @param pin The GPIO pin.
/// @return 0 if successful, or an error code.
/// @retval -EINVAL if the GPIO pin is invalid.
/// @retval -EIO if a GPIO error occured.
int mort_gpio_toggle(mort_gpio_pin_e pin);

/// @brief Attach an interrupt handler to a GPIO pin.
/// @param pin The GPIO pin.
/// @param event The event to trigger the interrupt on. Ignored if cb is NULL.
/// @param cb The interrupt handler. Set to NULL to remove in installed interrupt.
/// @return 0 if successful, or an error code.
/// @retval -EINVAL if the GPIO pin is invalid or the event is invalid.
/// @retval -EIO if a GPIO error occured.
int mort_gpio_attach_interrupt(
    mort_gpio_pin_e pin, mort_gpio_event_e event, mort_gpio_int_handler_cb cb);
