#pragma once

#include "util/stdinc.h"

#define MORT_CNT_NEC 0

/// @brief Initialize the counter HAL.
/// @return 0 if successful, or -EIO if an error occurred.
int mort_counter_init(void);

/// @brief Start the counter.
int mort_counter_start(int id);

/// @brief Stop the counter.
int mort_counter_stop(int id);

/// @brief Get the current count value of the counter.
/// @param id The ID of the counter to get the count value of.
/// @param o_count The output parameter to store the count value in.
/// @return 0 if successful, or an error code if an error occurred.
/// @retval -ENODEV The counter is not initialized.
/// @retval -EIO The counter could not be read.
/// @retval -EINVAL The counter ID is invalid, or the output parameter is NULL.
int mort_counter_get_count(int id, uint32_t *o_count);

