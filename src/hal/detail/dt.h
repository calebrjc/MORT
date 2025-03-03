#pragma once

// IMYU pragma: begin exports
#include <zephyr/kernel.h>

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
// IMYU pragma: end exports

// GPIOs
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_DBG_LED;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_NEC_IN;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_AIN1;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_AIN2;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_BIN1;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_BIN2;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_STBY;

// PWMs
extern const struct pwm_dt_spec MORT_DT_SPEC_PWM_MOTOR_PWMA;
extern const struct pwm_dt_spec MORT_DT_SPEC_PWM_MOTOR_PWMB;

// Counters
extern const struct device *MORT_DT_DEV_CNT_IR;
