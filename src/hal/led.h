#pragma once

#include "util/stdinc.h"

// LED masks
#define MORT_LED_DEBUG 1 << 0
#define MORT_LED_ALL   UINT32_MAX

/// @brief Initialize the LED HAL.
/// @return 0 if successful, or -EIO if an error occurred.
int mort_led_init(void);

/// @brief Set the state of the LEDs.
/// @param led_mask The mask of LEDs to set.
/// @param state The state to set the LEDs to (0 or 1).
/// @return 0 if successful, or -EIO if an error occurred.
int mort_led_set_state(uint32_t led_mask, int state);

/// @brief Toggle the state of the LEDs.
/// @param led_mask The mask of LEDs to toggle.
/// @return 0 if successful, or -EIO if an error occurred.
int mort_led_toggle(uint32_t led_mask);
