#pragma once

#include "hal/gpio.h"
#include "hal/pwm.h"
#include "util/stdinc.h"

typedef enum
{
    MORT_TB6612FNG_DC_MOTOR_A = 0,
    MORT_TB6612FNG_DC_MOTOR_B,
    MORT_TB6612FNG_DC_MOTOR_MAX,
} mort_tb6612fng_dc_motor_e;

typedef enum
{
    MORT_TB6612FNG_DC_MODE_CCW = 0,
    MORT_TB6612FNG_DC_MODE_CW,
    MORT_TB6612FNG_DC_MODE_SHORT_BRAKE,
    MORT_TB6612FNG_DC_MODE_STOP,
    MORT_TB6612FNG_DC_MODE_MAX,
} mort_tb6612fng_dc_mode_e;

typedef struct
{
    mort_pwm_channel_e pwm;
    mort_gpio_pin_e    in1;
    mort_gpio_pin_e    in2;
} mort_tb6612fng_dc_motor_init_t;

/// @brief Initialize the TB6612FNG_DC driver.
/// @param[in] motora_init Optional; Init structure for the motor A.
/// @param[in] motorb_init Optional; Init structure for the motor B.
/// @param[in] standby_pin Optional; GPIO pin for the standby signal.
///                         (set as MORT_GPIO_PIN_MAX if not used).
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_tb6612fng_dc_init(
    mort_tb6612fng_dc_motor_init_t *motora_init,
    mort_tb6612fng_dc_motor_init_t *motorb_init,
    mort_gpio_pin_e                 standby_pin);

/// @brief Set the mode of a motor.
/// @param[in] motor The motor to set the mode for.
/// @param[in] mode The mode to set.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if an invalid motor or mode is given.
/// @retval -EIO if an error occurred.
int mort_tb6612fng_dc_set_mode(mort_tb6612fng_dc_motor_e motor, mort_tb6612fng_dc_mode_e mode);

/// @brief Set the standby mode.
/// @param[in] standby The standby mode to set.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if an invalid pin is configured as the standby pin.
/// @retval -EIO if an error occurred.
int mort_tb6612fng_dc_set_standby(bool standby);

/// @brief Set the speed of a motor.
/// @param[in] motor The motor to set the speed for.
/// @param[in] speed_pct The speed to set in percent.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if an invalid motor is given.
/// @retval -EIO if an error occurred.
int mort_tb6612fng_dc_set_speed(mort_tb6612fng_dc_motor_e motor, int speed_pct);
