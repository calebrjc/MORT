#pragma once

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define __MORT_DT_NODE_DEBUG_LED DT_ALIAS(led0)
#define __MORT_DT_NODE_IR_COUNTER DT_NODELABEL(counter3)

extern const struct gpio_dt_spec MORT_DT_SPEC_DEBUG_LED;
extern const struct device *MORT_DT_DEV_IR_COUNTER;
