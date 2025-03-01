#pragma once

#include "util/stdinc.h"

// LED masks
#define MORT_LED_DEBUG 1 << 0
#define MORT_LED_ALL   UINT32_MAX

/// @brief Set the state of the LEDs.
/// @param [in] led_mask The mask of LEDs to set.
/// @param [in] state The state to set the LEDs to (0 or 1).
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_led_set_state(uint32_t led_mask, int state);

/// @brief Toggle the state of the LEDs.
/// @param [in] led_mask The mask of LEDs to toggle.
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_led_toggle(uint32_t led_mask);
