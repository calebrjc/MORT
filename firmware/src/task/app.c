#include "task/app.h"

#include <zephyr/kernel.h>

#include "driver/nec.h"
#include "hal/counter.h"
#include "hal/gpio.h"
#include "util/debug.h"

#define __MORT_APP_TASK_QUEUE_SIZE 10

// Events ------------------------------------------------------------------------------------------

typedef enum
{
    __MORT_APP_TASK_EVT_NEC_DATA_RECV = 0,
} __mort_app_task_event_e;

typedef struct
{
    mort_nec_button_e button;
} __mort_app_task_event_nec_data_recv_t;

typedef struct
{
    __mort_app_task_event_e id;

    union
    {
        __mort_app_task_event_nec_data_recv_t nec_data_recv;
    };
} __mort_app_task_event_t;

/// @brief Handle an NEC data received event.
/// @param[in] event The event to handle.
void __mort_app_task_handle_nec_data_recv(const __mort_app_task_event_nec_data_recv_t *event);

// Callbacks ---------------------------------------------------------------------------------------

/// @brief Handle an NEC data received interrupt.
/// @param[in] data The NEC data that was received.
void __mort_app_task_on_nec_data_ready(mort_nec_button_e data);

// -------------------------------------------------------------------------------------------------

K_MSGQ_DEFINE(s_task_queue, sizeof(__mort_app_task_event_t), __MORT_APP_TASK_QUEUE_SIZE, 1);

int mort_app_task_init(void)
{
    int ec = 0;

    ec = mort_nec_init(MORT_GPIO_PIN_NEC_IN, MORT_CNT_NEC, __mort_app_task_on_nec_data_ready);
    MORT_RETURN_LOGE_IF(ec < 0, -1, "Failed to initialize NEC driver");

    MORT_LOGI("App task initialized");
    return 0;
}

void mort_app_task_run(void)
{
    __mort_app_task_event_t event = {0};

    MORT_LOGI("App task started");

    while (1)
    {
        int ec = k_msgq_get(&s_task_queue, &event, K_FOREVER);
        if (ec < 0)
        {
            MORT_LOGE("Failed to get event from queue (ec %d)", ec);
            continue;
        }

        switch (event.id)
        {
            case __MORT_APP_TASK_EVT_NEC_DATA_RECV:
                __mort_app_task_handle_nec_data_recv(&event.nec_data_recv);
                break;

            default:
                MORT_CRASH("App task received unknown event ID %d", event.id);
        }
    }

    // NOTE(Caleb): We should never get to this point
    MORT_CRASH("App task exited");
}

void __mort_app_task_on_nec_data_ready(mort_nec_button_e data)
{
    __mort_app_task_event_t event = {0};
    event.id                      = __MORT_APP_TASK_EVT_NEC_DATA_RECV;
    event.nec_data_recv.button    = data;

    // NOTE(Caleb): Return value intentionally ignored. If this fails, we'll just drop the event.
    k_msgq_put(&s_task_queue, &event, K_NO_WAIT);
}

void __mort_app_task_handle_nec_data_recv(const __mort_app_task_event_nec_data_recv_t *event)
{
    MORT_LOGN("Button pressed: %s", mort_nec_button_to_string(event->button));
}
