#include "hal/counter.h"

#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/kernel.h>

#include "hal/detail/dt.h"
#include "util/debug.h"

int mort_counter_init(void)
{
    bool ok = device_is_ready(MORT_DT_DEV_COUNTER_IR);
    MORT_RETURN_LOGE_IF(!ok, -EIO, "IR counter device is not ready");

    uint32_t mtv = counter_get_max_top_value(MORT_DT_DEV_COUNTER_IR);
    MORT_LOGD("Max top value of the IR counter: %u", mtv);

#if (0)
    struct counter_top_cfg top_cfg = {.ticks = 0xFFFF};
    int                    ec      = counter_set_top_value(MORT_DT_DEV_COUNTER_IR, &top_cfg);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to set the top value of the IR counter (ec: %d)", ec);
#endif

    return 0;
}

int mort_counter_start(int id)
{
    int ec = counter_start(MORT_DT_DEV_COUNTER_IR);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to start the IR counter");

    struct counter_top_cfg top_cfg = {.ticks = 0xFFFF};
    ec                             = counter_set_top_value(MORT_DT_DEV_COUNTER_IR, &top_cfg);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to set the top value of the IR counter (ec: %d)", ec);

    return 0;
}

int mort_counter_stop(int id)
{
    int ec = counter_stop(MORT_DT_DEV_COUNTER_IR);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to stop the IR counter");

    return 0;
}

int mort_counter_get_count(int id, uint32_t *o_count)
{
    int ec = counter_get_value(MORT_DT_DEV_COUNTER_IR, o_count);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to get the count value of the IR counter");

    return 0;
}
