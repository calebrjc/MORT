#include "hal/counter.h"
#include "hal/gpio.h"
#include "hal/pwm.h"
#include "task/app.h"
#include "util/debug.h"

int main(void)
{
    int ec = 0;

    ec = mort_gpio_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the GPIO");

    ec = mort_counter_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the counter");

    ec = mort_pwm_init(MORT_PWM_CH_MOTORR);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the MOTORR PWM");

    ec = mort_pwm_init(MORT_PWM_CH_MOTORL);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the MOTORL PWM");

    ec = mort_app_task_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the app task");

    mort_app_task_run();

    // NOTE(Caleb): We should never get to this point
    return 0;
}
