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
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_gpio_init(void);

/// @brief Set the state of a GPIO pin.
/// @param [in] pin The GPIO pin.
/// @param [in] state The state to set the pin to.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if the GPIO pin is invalid.
/// @retval -EIO if an error occured.
int mort_gpio_set(mort_gpio_pin_e pin, int state);

/// @brief Toggle a GPIO pin.
/// @param [in] pin The GPIO pin.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if the GPIO pin is invalid.
/// @retval -EIO if an error occured.
int mort_gpio_toggle(mort_gpio_pin_e pin);

/// @brief Attach an interrupt to a GPIO pin.
/// @param [in] pin The GPIO pin.
/// @param [in] event The event to attach the interrupt to.
/// @param [in] cb The callback to call when the interrupt occurs.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if the GPIO pin is invalid or the event is invalid.
/// @retval -EIO if an error occured.
int mort_gpio_attach_interrupt(
    mort_gpio_pin_e pin, mort_gpio_event_e event, mort_gpio_int_handler_cb cb);
