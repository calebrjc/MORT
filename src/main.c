#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "hal/led.h"
#include "util/debug.h"

int main(void)
{
    int ec = 0;

    ec = mort_led_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the debug LED");

    while (1)
    {
        MORT_DEBUG_LED_TOGGLE();
        k_sleep(K_MSEC(1000));
    }

    return 0;
}
