#pragma once

#include "util/stdinc.h"

typedef enum
{
    MORT_CNT_NEC = 0,
} mort_counter_e;

typedef void (*mort_counter_on_overflow_cb)(void);

/// @brief Initialize the counter HAL.
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_counter_init(void);

// TODO(Caleb): Document counter value validation return code?
/// @brief Reset and start a counter.
/// @param[in] counter The counter to start.
/// @param[in] top_value The top value of the counter.
/// @param[in] cb [optional] The callback to call when the counter overflows.
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_counter_start(mort_counter_e counter, uint32_t top_value, mort_counter_on_overflow_cb cb);

/// @brief Stop a counter.
/// @param[in] counter The counter to stop.
/// @retval 0 if the operation was successful.
/// @retval -EIO if an error occurred.
int mort_counter_stop(mort_counter_e counter);

/// @brief Get the current value of a counter.
/// @param[in] counter The counter to get the value of.
/// @param[out] o_count The current value of the counter.:w
/// @retval 0 if the operation was successful.
/// @retval -EINVAL if `o_count` is NULL.
/// @retval -EIO if an error occurred.
int mort_counter_get_count(mort_counter_e counter, uint32_t *o_count);
