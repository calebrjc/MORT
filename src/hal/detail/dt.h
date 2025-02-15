#pragma once

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

// TODO(Caleb): Identify peripherals in the DT and use those names here.

// Node Names ------------------------------------------------------------------

#define __MORT_DT_NODE_GPIO_DBG_LED DT_ALIAS(led0)
#define __MORT_DT_NODE_GPIO_NEC_IN  DT_NODELABEL(load_switch)

#define __MORT_DT_NODE_COUNTER_IR   DT_NODELABEL(counter3)

// Specs and Devices -----------------------------------------------------------

extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_DBG_LED;
extern const struct gpio_dt_spec MORT_DT_SPEC_GPIO_NEC_IN;

extern const struct device *MORT_DT_DEV_COUNTER_IR;
