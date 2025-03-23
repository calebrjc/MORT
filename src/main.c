#include <zephyr/kernel.h>

#include "driver/nec.h"
#include "driver/tb6612fng_dc.h"
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

    mort_tb6612fng_dc_motor_init_t motora_init = {
        MORT_PWM_CH_MOTORR, MORT_GPIO_PIN_MOTOR_AIN1, MORT_GPIO_PIN_MOTOR_AIN2};
    mort_tb6612fng_dc_motor_init_t motorb_init = {
        MORT_PWM_CH_MOTORL, MORT_GPIO_PIN_MOTOR_BIN1, MORT_GPIO_PIN_MOTOR_BIN2};
    ec = mort_tb6612fng_dc_init(&motora_init, &motorb_init, MORT_GPIO_PIN_MOTOR_STBY);
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the TB6612FNG_DC");

    mort_tb6612fng_dc_set_standby(false);
    mort_tb6612fng_dc_set_mode(MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_CW);
    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 100);

    while (1)
    {
        if (!s_printed)
        {
            MORT_LOGN("Button %s", mort_nec_button_to_string(s_last_button_pressed));
            s_printed = true;

            switch (s_last_button_pressed)
            {
                case MORT_NEC_BTN_UP:
                {
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_CW);
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_B, MORT_TB6612FNG_DC_MODE_CCW);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 40);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_B, 40);
                    break;
                }

                case MORT_NEC_BTN_DOWN:
                {
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_CCW);
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_B, MORT_TB6612FNG_DC_MODE_CW);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 40);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_B, 40);
                    break;
                }

                case MORT_NEC_BTN_LEFT:
                {
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_SHORT_BRAKE);
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_B, MORT_TB6612FNG_DC_MODE_CCW);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 40);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_B, 40);
                    break;
                }

                case MORT_NEC_BTN_RIGHT:
                {
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_CW);
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_B, MORT_TB6612FNG_DC_MODE_SHORT_BRAKE);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 40);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_B, 40);
                    break;
                }

                case MORT_NEC_BTN_NONE:
                {
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_A, MORT_TB6612FNG_DC_MODE_STOP);
                    mort_tb6612fng_dc_set_mode(
                        MORT_TB6612FNG_DC_MOTOR_B, MORT_TB6612FNG_DC_MODE_STOP);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_A, 0);
                    mort_tb6612fng_dc_set_speed(MORT_TB6612FNG_DC_MOTOR_B, 0);
                    break;
                }

                default:
                    break;
            }
        }

        k_sleep(K_MSEC(16));
    }
#endif

    // NOTE(Caleb): We should never get to this point
    return 0;
}
