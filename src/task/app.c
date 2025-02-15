#include "task/app.h"

#include "util/debug.h"

int mort_app_task_init(void)
{
    // TODO(Caleb): Add initialization code here.

    MORT_LOGI("App task initialized");
    return 0;
}

void mort_app_task_run(void)
{
    // TODO(Caleb): Add main application task code here.
    MORT_LOGI("App task started");

    while (1)
    {
        // ...
    }
}
