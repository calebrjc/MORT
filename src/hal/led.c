#include "hal/led.h"

#include "hal/detail/dt.h"
#include "util/debug.h"

int mort_led_init(void)
{
    bool ok = false;
    int  ec = 0;

    ok = gpio_is_ready_dt(&MORT_DT_SPEC_GPIO_DBG_LED);
    MORT_RETURN_LOGE_IF(!ok, -EIO, "Debug LED is not ready");

    ec = gpio_pin_configure_dt(&MORT_DT_SPEC_GPIO_DBG_LED, GPIO_OUTPUT_ACTIVE);
    MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to configure the debug LED");

    return 0;
}

int mort_led_set_state(uint32_t led_mask, int state)
{
    MORT_LOGW_IF(led_mask == 0, "No LEDs selected in a call to mort_led_set_state()");

    if (led_mask & MORT_LED_DEBUG)
    {
        int ec = gpio_pin_set_dt(&MORT_DT_SPEC_GPIO_DBG_LED, state);
        MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to set the debug LED state");
    }

    return 0;
}

int mort_led_toggle(uint32_t led_mask)
{
    MORT_LOGW_IF(led_mask == 0, "No LEDs selected in a call to mort_led_toggle()");

    if (led_mask & MORT_LED_DEBUG)
    {
        int ec = gpio_pin_toggle_dt(&MORT_DT_SPEC_GPIO_DBG_LED);
        MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to toggle the debug LED");
    }

    return 0;
}
