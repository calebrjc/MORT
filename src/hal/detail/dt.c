#include "hal/detail/dt.h"
#include "zephyr/device.h"
#include "zephyr/drivers/gpio.h"

const struct gpio_dt_spec MORT_DT_SPEC_GPIO_DBG_LED =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_DBG_LED, gpios);
const struct gpio_dt_spec MORT_DT_SPEC_GPIO_NEC_IN =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_GPIO_NEC_IN, gpios);

const struct device *MORT_DT_DEV_COUNTER_IR = DEVICE_DT_GET(__MORT_DT_NODE_COUNTER_IR);
