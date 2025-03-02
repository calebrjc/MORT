#pragma once

#include "util/stdinc.h"

// TODO(Caleb): Document this file

typedef enum
{
    MORT_PWM_CH_MOTORR = 0,
    MORT_PWM_CH_MOTORL,
    MORT_PWM_CH_MAX,
} mort_pwm_channel_e;

int mort_pwm_init(mort_pwm_channel_e channel);
int mort_pwm_set_duty_cycle(mort_pwm_channel_e channel, int duty_cycle_pct);

