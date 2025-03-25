#pragma once

#include "util/stdinc.h"

typedef enum
{
    MORT_PWM_CH_MOTORR = 0,
    MORT_PWM_CH_MOTORL,
    MORT_PWM_CH_MAX,
} mort_pwm_channel_e;

/// @brief Initialize a PWM channel.
/// @param channel The channel to initialize.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if an invalid channel is given.
/// @retval -EIO if a system error occurrs.
int mort_pwm_init(mort_pwm_channel_e channel);

/// @brief Set the duty cycle of a PWM channel.
/// @param channel The channel to set the duty cycle for.
/// @param duty_cycle_pct The duty cycle to set in percent.
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if an invalid channel or duty cycle is given.
/// @retval -EIO if a system error occurrs.
int mort_pwm_set_duty_cycle(mort_pwm_channel_e channel, int duty_cycle_pct);
