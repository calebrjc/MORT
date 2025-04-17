#include "hal/detail/dt.h"

#include <zephyr/device.h>

// Node Names ------------------------------------------------------------------

#define __MORT_DT_NODE_GPIOS           DT_NODELABEL(gpios)
#define __MORT_DT_NODE_GPIO_DBG_LED    DT_CHILD(__MORT_DT_NODE_GPIOS, debug_led)
#define __MORT_DT_NODE_GPIO_NEC_IN     DT_CHILD(__MORT_DT_NODE_GPIOS, nec_in)
#define __MORT_DT_NODE_GPIO_MOTOR_AIN1 DT_CHILD(__MORT_DT_NODE_GPIOS, motor_ain1)
#define __MORT_DT_NODE_GPIO_MOTOR_AIN2 DT_CHILD(__MORT_DT_NODE_GPIOS, motor_ain2)
#define __MORT_DT_NODE_GPIO_MOTOR_BIN1 DT_CHILD(__MORT_DT_NODE_GPIOS, motor_bin1)
#define __MORT_DT_NODE_GPIO_MOTOR_BIN2 DT_CHILD(__MORT_DT_NODE_GPIOS, motor_bin2)
#define __MORT_DT_NODE_GPIO_MOTOR_STBY DT_CHILD(__MORT_DT_NODE_GPIOS, motor_stby)

#define __MORT_DT_NODE_PWMS            DT_NODELABEL(pwms)
#define __MORT_DT_NODE_PWM_MOTOR_PWMA  DT_CHILD(__MORT_DT_NODE_PWMS, motor_pwma)
#define __MORT_DT_NODE_PWM_MOTOR_PWMB  DT_CHILD(__MORT_DT_NODE_PWMS, motor_pwmb)

#define __MORT_DT_NODE_COUNTER_IR      DT_NODELABEL(counter3)

// Specs and Devices -----------------------------------------------------------

const struct device      *MORT_GPIOA = DEVICE_DT_GET(DT_NODELABEL(gpioa));
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_DBG_LED =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_DBG_LED, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_NEC_IN =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_NEC_IN, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_AIN1 =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_MOTOR_AIN1, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_AIN2 =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_MOTOR_AIN2, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_BIN1 =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_MOTOR_BIN1, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_BIN2 =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_MOTOR_BIN2, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_MOTOR_STBY =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_MOTOR_STBY, gpios);

const struct pwm_dt_spec MORT_DT_SPEC_PWM_MOTOR_PWMA =
    PWM_DT_SPEC_GET(__MORT_DT_NODE_PWM_MOTOR_PWMA);
const struct pwm_dt_spec MORT_DT_SPEC_PWM_MOTOR_PWMB =
    PWM_DT_SPEC_GET(__MORT_DT_NODE_PWM_MOTOR_PWMB);

const struct device *MORT_DT_DEV_CNT_IR = DEVICE_DT_GET(__MORT_DT_NODE_COUNTER_IR);
