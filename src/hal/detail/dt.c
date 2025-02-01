#include "hal/detail/dt.h"

const struct gpio_dt_spec MORT_DT_SPEC_DEBUG_LED =
    GPIO_DT_SPEC_GET(__MORT_DT_NODE_DEBUG_LED, gpios);
