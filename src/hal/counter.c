#include "hal/counter.h"

#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/kernel.h>

#include "hal/detail/dt.h"
#include "util/compiler.h"
#include "util/debug.h"

// NOTE(Caleb):
// Currently, MORT only uses one timer. This implementation will need to be modified when there are
// more.

/// @brief Counter overflow callback function.
/// @param [in] dev The counter device on which the overflow occurred.
/// @param [in] user_data User data passed to the callback function.
static void __mort_counter_on_overflow_cb(const struct device *dev, void *user_data);

// -----------------------------------------------------------------------------

static mort_counter_on_overflow_cb s_on_overflow_cb;

// -----------------------------------------------------------------------------

int mort_counter_init(void)
{
    bool ok = device_is_ready(MORT_DT_DEV_CNT_IR);
    MORT_RETURN_LOGE_IF(!ok, -EIO, "IR counter device is not ready");

    uint32_t mtv = counter_get_max_top_value(MORT_DT_DEV_CNT_IR);
    MORT_LOGD("Max top value of the IR counter: %u", mtv);

    return 0;
}

int mort_counter_start(mort_counter_e counter, uint32_t top_value, mort_counter_on_overflow_cb cb)
{
    int ec = counter_start(MORT_DT_DEV_CNT_IR);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to start the IR counter");

    s_on_overflow_cb               = cb;
    struct counter_top_cfg top_cfg = {
        .ticks = top_value, .callback = __mort_counter_on_overflow_cb};
    ec = counter_set_top_value(MORT_DT_DEV_CNT_IR, &top_cfg);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to set the top value of the IR counter (ec: %d)", ec);

    return 0;
}

int mort_counter_stop(mort_counter_e counter)
{
    int ec = counter_stop(MORT_DT_DEV_CNT_IR);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to stop the IR counter");

    return 0;
}

int mort_counter_get_count(mort_counter_e counter, uint32_t *o_count)
{
    MORT_RETURN_LOGE_IF(!o_count, -EINVAL, "o_count is NULL");

    int ec = counter_get_value(MORT_DT_DEV_CNT_IR, o_count);
    MORT_RETURN_LOGE_IF(ec, -EIO, "Failed to get the count value of the IR counter");

    return 0;
}

static void __mort_counter_on_overflow_cb(const struct device *dev, void *user_data)
{
    MORT_UNUSED(dev);
    MORT_UNUSED(user_data);

    if (s_on_overflow_cb)
    {
        s_on_overflow_cb();
    }
}
