#include "hal/detail/dt.h"

const struct gpio_dt_spec MORT_DT_SPEC_DEBUG_LED =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_DEBUG_LED, gpios);
const struct device *MORT_DT_DEV_IR_COUNTER = DEVICE_DT_GET(__MORT_DT_NODE_IR_COUNTER);
