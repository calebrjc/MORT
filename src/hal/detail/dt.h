#pragma once

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define __MORT_DT_NODE_DEBUG_LED DT_ALIAS(led0)

extern const struct gpio_dt_spec MORT_DT_SPEC_DEBUG_LED;
