#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "hal/counter.h"
#include "hal/led.h"
#include "task/app.h"
#include "util/debug.h"
#include "util/stdinc.h"
#include "zephyr/dt-bindings/gpio/gpio.h"

static const struct gpio_dt_spec test = GPIO_DT_SPEC_GET(DT_NODELABEL(load_switch), gpios);

static struct gpio_callback ir_cb       = {0};
static int                  pulse_count = 0;

// 1ms = 10000 counts

uint32_t pulse_timings[34] = {0};

union
{
    struct
    {
        uint8_t address;
        uint8_t address_inv;
        uint8_t command;
        uint8_t command_inv;
    };
    uint32_t raw;
} ir_data;
;

void on_ir_falling_edge(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    uint32_t count = 0;
    mort_counter_get_count(MORT_CNT_NEC, &count);
    pulse_timings[pulse_count] = count;

    mort_counter_stop(MORT_CNT_NEC);
    mort_counter_start(MORT_CNT_NEC);

    if (pulse_count == 0)
    {
        ir_data.raw = 0;
    }

    if (2 <= pulse_count && pulse_count < 34)
    {
        int bit = (pulse_timings[pulse_count] > 170) ? 1 : 0;
        ir_data.raw |= bit << (pulse_count - 2);
    }

    pulse_count++;
}

int main(void)
{
    int ec = 0;

    // TODO(Caleb): mort_hal_init()
    ec = mort_led_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the debug LED");

    ec = mort_counter_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the counter");

    ec = mort_app_task_init();
    MORT_ASSERT_MSG(ec == 0, "Failed to initialize the app task");

#if (0)
    mort_app_task_run();
#else
    // ec = mort_counter_start(MORT_CNT_NEC);
    // MORT_ASSERT_MSG(ec == 0, "Failed to start the counter");

    gpio_pin_configure_dt(&test, GPIO_INPUT | GPIO_PULL_DOWN);
    gpio_pin_interrupt_configure_dt(&test, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&ir_cb, on_ir_falling_edge, BIT(test.pin));
    gpio_add_callback_dt(&test, &ir_cb);

    while (1)
    {
        if (pulse_count >= 34)
        {
            MORT_LOGI("Pulse timings (falling edge to falling edge):");
            for (int i = 0; i < 34; i++)
            {
                MORT_LOGI(
                    "Pulse %.02d: %d (%u)", i, pulse_timings[i], (pulse_timings[i] > 200) ? 1 : 0);
            }

            MORT_LOGI(
                "Address: 0x%02x, Address Inv: 0x%02x, Command: 0x%02x, Command Inv: 0x%02x",
                ir_data.address,
                ir_data.address_inv,
                ir_data.command,
                ir_data.command_inv);

            pulse_count = 0;
        }

        k_sleep(K_MSEC(100));
    }
#endif
    // NOTE(Caleb): We should never get to this point
    return 0;
}
