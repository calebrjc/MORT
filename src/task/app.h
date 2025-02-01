#pragma once

/// @brief Initialize the application task.
/// @return 0 if successful, and < 0 if an error occurred.
int mort_app_task_init(void);

/// @brief Run the application task.
/// @note This function should be called at the end of the main function, and will never return.
void mort_app_task_run(void);
