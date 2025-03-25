#include "driver/tb6612fng_dc.h"

#include "hal/gpio.h"
#include "hal/pwm.h"
#include "util/debug.h"

typedef struct
{
    bool                           initialized;
    mort_tb6612fng_dc_motor_init_t pins;
} __mort_tb6612fng_dc_motor_ctx_t;

static __mort_tb6612fng_dc_motor_ctx_t s_motors[MORT_TB6612FNG_DC_MOTOR_MAX] = {0};
static mort_gpio_pin_e                 s_standby_pin                         = MORT_GPIO_PIN_MAX;

int mort_tb6612fng_dc_init(
    mort_tb6612fng_dc_motor_init_t *motora_init,
    mort_tb6612fng_dc_motor_init_t *motorb_init,
    mort_gpio_pin_e                 standby_pin)
{
    if (motora_init)
    {
        s_motors[MORT_TB6612FNG_DC_MOTOR_A].pins        = *motora_init;
        s_motors[MORT_TB6612FNG_DC_MOTOR_A].initialized = true;
    }

    if (motora_init)
    {
        s_motors[MORT_TB6612FNG_DC_MOTOR_B].pins        = *motorb_init;
        s_motors[MORT_TB6612FNG_DC_MOTOR_B].initialized = true;
    }

    s_standby_pin = standby_pin;

    return 0;
}

int mort_tb6612fng_dc_set_mode(mort_tb6612fng_dc_motor_e motor, mort_tb6612fng_dc_mode_e mode)
{
    MORT_RETURN_LOGE_IF(
        motor >= MORT_TB6612FNG_DC_MOTOR_MAX,
        -EINVAL,
        "Failed to set motor mode: Invalid motor ID");
    MORT_RETURN_LOGE_IF(
        mode >= MORT_TB6612FNG_DC_MODE_MAX,
        -EINVAL,
        "Failed to set motor mode: Invalid mode %d",
        mode);

    const __mort_tb6612fng_dc_motor_ctx_t *motor_ctx = &s_motors[motor];
    MORT_ASSERT_MSG(
        motor_ctx, "Failed to set motor mode: Invalid motor context (motor ID %d)", motor);
    MORT_ASSERT_MSG(motor_ctx->initialized, "Failed to set motor mode: Motor is not initialized");

    int ec = 0;

    switch (mode)
    {
        case MORT_TB6612FNG_DC_MODE_CCW:
        {
            ec = mort_gpio_set(motor_ctx->pins.in1, 0);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            ec = mort_gpio_set(motor_ctx->pins.in2, 1);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            break;
        }

        case MORT_TB6612FNG_DC_MODE_CW:
        {
            ec = mort_gpio_set(motor_ctx->pins.in1, 1);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            ec = mort_gpio_set(motor_ctx->pins.in2, 0);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            break;
        }

        case MORT_TB6612FNG_DC_MODE_SHORT_BRAKE:
        {
            ec = mort_gpio_set(motor_ctx->pins.in1, 1);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            ec = mort_gpio_set(motor_ctx->pins.in2, 1);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            break;
        }

        case MORT_TB6612FNG_DC_MODE_STOP:
        {
            ec = mort_gpio_set(motor_ctx->pins.in1, 0);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            ec = mort_gpio_set(motor_ctx->pins.in2, 0);
            MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor mode: Failed to set GPIO pin");

            break;
        }

        default:
            MORT_CRASH("Failed to set motor mode: Invalid mode");
    }

    return 0;
}

int mort_tb6612fng_dc_set_standby(bool standby)
{
    MORT_RETURN_LOGE_IF(
        s_standby_pin >= MORT_GPIO_PIN_MAX,
        -EINVAL,
        "Failed to change standby mode: No standby pin set");

    int ec = mort_gpio_set(s_standby_pin, !standby);
    MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to change standby mode: Failed to set GPIO pin");

    return 0;
}

int mort_tb6612fng_dc_set_speed(mort_tb6612fng_dc_motor_e motor, int speed_pct)
{
    MORT_RETURN_LOGE_IF(
        motor >= MORT_TB6612FNG_DC_MOTOR_MAX,
        -EINVAL,
        "Failed to set motor speed: Invalid motor ID");
    MORT_RETURN_LOGE_IF(
        speed_pct < 0 || 100 < speed_pct, -EINVAL, "Failed to set motor speed: Invalid speed");

    const __mort_tb6612fng_dc_motor_ctx_t *motor_ctx = &s_motors[motor];
    MORT_ASSERT_MSG(
        motor_ctx, "Failed to set motor speed: Invalid motor context (motor ID %d)", motor);
    MORT_ASSERT_MSG(motor_ctx->initialized, "Failed to set motor speed: Motor is not initialized");

    int ec = mort_pwm_set_duty_cycle(motor_ctx->pins.pwm, speed_pct);
    MORT_RETURN_LOGE_IF(ec < 0, ec, "Failed to set motor speed: Failed to set PWM duty cycle");

    return 0;
}
