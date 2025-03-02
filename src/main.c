#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "driver/nec.h"
#include "hal/counter.h"
#include "hal/gpio.h"
#include "hal/pwm.h"
#include "task/app.h"
#include "util/debug.h"
#include "util/stdinc.h"

static mort_nec_button_e s_last_button_pressed = MORT_NEC_BTN_NONE;
static bool              s_printed             = true;

void on_nec_data_ready(mort_nec_button_e data)
{
    s_last_button_pressed = data;
    s_printed             = false;
}

int main(void)
{
    int ec = 0;

    // TODO(Caleb): mort_hal_init()?

    ec = mort_gpio_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the GPIO");

    ec = mort_counter_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the counter");

    ec = mort_nec_init(MORT_GPIO_PIN_NEC_IN, MORT_CNT_NEC, on_nec_data_ready);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the NEC");

    ec = mort_app_task_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the app task");

#if (0)
    mort_app_task_run();
#else
    ec = mort_pwm_init(MORT_PWM_CH_MOTORR);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the PWM");

    ec = mort_pwm_init(MORT_PWM_CH_MOTORL);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the PWM");

    ec = mort_pwm_set_duty_cycle(MORT_PWM_CH_MOTORR, 50);
    MORT_ASSERT_MSG(ec == 0, "Failed to set the duty cycle");

    ec = mort_pwm_set_duty_cycle(MORT_PWM_CH_MOTORL, 50);
    MORT_ASSERT_MSG(ec == 0, "Failed to set the duty cycle");

    while (1)
    {
        k_sleep(K_MSEC(100));
    }
#endif
    // NOTE(Caleb): We should never get to this point
    return 0;
}
