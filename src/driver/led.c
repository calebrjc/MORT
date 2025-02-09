#include "driver/led.h"

#include "hal/gpio.h"
#include "util/debug.h"

int mort_led_set_state(uint32_t led_mask, int state)
{
    MORT_LOGW_IF(led_mask == 0, "No LEDs selected in a call to mort_led_set_state()");

    if (led_mask & MORT_LED_DEBUG)
    {
        int ec = mort_gpio_set(MORT_GPIO_PIN_DBG_LED, state);
        MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to set the debug LED state");
    }

    return 0;
}

int mort_led_toggle(uint32_t led_mask)
{
    MORT_LOGW_IF(led_mask == 0, "No LEDs selected in a call to mort_led_toggle()");

    if (led_mask & MORT_LED_DEBUG)
    {
        int ec = mort_gpio_toggle(MORT_GPIO_PIN_DBG_LED);
        MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to toggle the debug LED");
    }

    return 0;
}
