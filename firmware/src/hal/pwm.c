#include "hal/pwm.h"

#include <zephyr/drivers/pwm.h>

#include "hal/detail/dt.h"
#include "util/debug.h"
#include "util/math.h"

// TODO(Caleb): Document this file

typedef struct
{
    const struct pwm_dt_spec *spec;
    bool                      initialized;
} __mort_pwm_ctx_t;

static __mort_pwm_ctx_t s_pwms[] = {
    [MORT_PWM_CH_MOTORR] = {&MORT_DT_SPEC_PWM_MOTOR_PWMA, false},
    [MORT_PWM_CH_MOTORL] = {&MORT_DT_SPEC_PWM_MOTOR_PWMB, false},
};

int mort_pwm_init(mort_pwm_channel_e channel)
{
    MORT_RETURN_LOGE_IF(
        channel >= MORT_PWM_CH_MAX,
        -EINVAL,
        "Failed to initialize PWM: Invalid channel ID %d",
        channel);

    __mort_pwm_ctx_t *pwm = &s_pwms[channel];

    bool ok = pwm_is_ready_dt(pwm->spec);
    MORT_RETURN_LOGE_IF(
        !ok, -EIO, "Failed to initialize PWM: PWM channel %d is not ready", channel);

    pwm->initialized = true;

    return 0;
}

int mort_pwm_set_duty_cycle(mort_pwm_channel_e channel, int duty_cycle_pct)
{
    MORT_RETURN_LOGE_IF(
        channel >= MORT_PWM_CH_MAX,
        -EINVAL,
        "Failed to enable PWM: Invalid channel ID %d",
        channel);

    MORT_RETURN_LOGE_IF(
        duty_cycle_pct < 0 || duty_cycle_pct > 100,
        -EINVAL,
        "Failed to enable PWM: Invalid duty cycle %d",
        duty_cycle_pct);

    const __mort_pwm_ctx_t *pwm = &s_pwms[channel];
    MORT_RETURN_LOGE_IF(
        !pwm->initialized,
        -EIO,
        "Failed to set duty cycle: PWM channel %d is not initialized",
        channel);

    int pulse = MORT_MAP(duty_cycle_pct, 0, 100, 0, pwm->spec->period);
    int ec    = pwm_set_pulse_dt(pwm->spec, pulse);
    MORT_RETURN_LOGE_IF(ec < 0, -EIO, "Failed to set duty cycle: Failed to set pulse (ec %d)", ec);

    return 0;
}
