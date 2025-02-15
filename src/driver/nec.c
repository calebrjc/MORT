#include "driver/nec.h"

#include "hal/counter.h"
#include "util/debug.h"
#include "util/math.h"

// NOTE(Caleb):
// This driver assumes a counter period of 10us (1.75ms = 175 ticks)

// NOTE(Caleb): ~115 for 0, ~225 for 1
#define __MORT_NEC_EDGE_COUNT_TO_BIT(__cnt_val) ((__cnt_val > 170) ? 1 : 0)

// -----------------------------------------------------------------------------

/// @brief Counter overflow callback.
void __mort_nec_on_counter_overflow(void);

/// @brief Check if an edge is valid given the length of its pulse.
/// @param[in] edge_count The edge number.
/// @param[in] counter_value The value of the counter (edge period).
static bool __mort_nec_is_edge_valid(uint32_t edge_count, uint32_t counter_value);

// -----------------------------------------------------------------------------

static uint32_t                 s_edge_count = 0;
static mort_nec_on_data_recv_cb s_cb         = NULL;

union __attribute__((packed))
{
    uint32_t raw;
    struct
    {
        uint8_t address;
        uint8_t address_inv;
        uint8_t command;
        uint8_t command_inv;
    };
} s_nec_data;

// -----------------------------------------------------------------------------

void mort_nec_set_callback(mort_nec_on_data_recv_cb cb)
{
    s_cb = cb;
}

const char *mort_nec_button_to_string(mort_nec_button_e button)
{
    static const char *__S_BTN_TO_STRING_LUT[] = {
        [MORT_NEC_BTN_VOLN]      = "MORT_NEC_BTN_VOLN",
        [MORT_NEC_BTN_PLAYPAUSE] = "MORT_NEC_BTN_PLAYPAUSE",
        [MORT_NEC_BTN_VOLP]      = "MORT_NEC_BTN_VOLP",
        [MORT_NEC_BTN_SETUP]     = "MORT_NEC_BTN_SETUP",
        [MORT_NEC_BTN_UP]        = "MORT_NEC_BTN_UP",
        [MORT_NEC_BTN_STOPMODE]  = "MORT_NEC_BTN_STOPMODE",
        [MORT_NEC_BTN_LEFT]      = "MORT_NEC_BTN_LEFT",
        [MORT_NEC_BTN_ENTERSAVE] = "MORT_NEC_BTN_ENTERSAVE",
        [MORT_NEC_BTN_RIGHT]     = "MORT_NEC_BTN_RIGHT",
        [MORT_NEC_BTN_010P]      = "MORT_NEC_BTN_010P",
        [MORT_NEC_BTN_DOWN]      = "MORT_NEC_BTN_DOWN",
        [MORT_NEC_BTN_BACK]      = "MORT_NEC_BTN_BACK",
        [MORT_NEC_BTN_1]         = "MORT_NEC_BTN_1",
        [MORT_NEC_BTN_2]         = "MORT_NEC_BTN_2",
        [MORT_NEC_BTN_3]         = "MORT_NEC_BTN_3",
        [MORT_NEC_BTN_4]         = "MORT_NEC_BTN_4",
        [MORT_NEC_BTN_5]         = "MORT_NEC_BTN_5",
        [MORT_NEC_BTN_6]         = "MORT_NEC_BTN_6",
        [MORT_NEC_BTN_7]         = "MORT_NEC_BTN_7",
        [MORT_NEC_BTN_8]         = "MORT_NEC_BTN_8",
        [MORT_NEC_BTN_9]         = "MORT_NEC_BTN_9",
    };

    if (button == MORT_NEC_BTN_NONE)
    {
        return "MORT_NEC_BTN_NONE";
    }

    return (button > MORT_NEC_BTN_MAX) ? "XXX" : __S_BTN_TO_STRING_LUT[button];
}

void mort_nec_on_falling_edge(void)
{
    // NOTE(Caleb): `mort_counter_*` error codes intentionally ignored.
    uint32_t count = 0;
    mort_counter_get_count(MORT_CNT_NEC, &count);

    mort_counter_stop(MORT_CNT_NEC);
    mort_counter_start(MORT_CNT_NEC, 10000, __mort_nec_on_counter_overflow);

    s_edge_count++;
    MORT_DEBUG_LED_TOGGLE();

    if (!__mort_nec_is_edge_valid(s_edge_count, count))
    {
        s_edge_count   = 0;
        s_nec_data.raw = 0;
    }

    if (3 <= s_edge_count && s_edge_count <= 34)
    {
        int bit = __MORT_NEC_EDGE_COUNT_TO_BIT(count);
        s_nec_data.raw |= bit << (s_edge_count - 3);
    }

    if (s_edge_count == 34 || (s_edge_count > 35 && MORT_IS_ODD(s_edge_count)))
    {
        if (s_cb)
        {
            s_cb((mort_nec_button_e)s_nec_data.command);
        }
    }
}

void __mort_nec_on_counter_overflow(void)
{
    mort_counter_stop(MORT_CNT_NEC);

    s_nec_data.raw = 0;
    s_edge_count   = 0;

    // NOTE(Caleb): Send command MORT_NEC_BTN_NONE to indicate button release.
    if (s_cb)
    {
        s_cb(MORT_NEC_BTN_NONE);
    }

    MORT_DEBUG_LED_OFF();
}

static bool __mort_nec_is_edge_valid(uint32_t edge_count, uint32_t counter_value)
{
    // NOTE(Caleb): These timing correspond to falling edge periods in the NEC output waveform.

    if (edge_count == 1)
    {
        return counter_value == 0;
    }
    else if (edge_count == 2)
    {
        return counter_value < 1500;
    }
    else if (3 <= edge_count && edge_count <= 34)
    {
        // NOTE(Caleb): ~115 for 0, ~225 for 1
        return counter_value < 300;
    }
    else if (edge_count == 35)
    {
        return counter_value < 4200;
    }
    else if (edge_count > 35 && MORT_IS_ODD(edge_count))
    {
        return counter_value < 10000;
    }
    else if (edge_count > 35 /* && MORT_IS_EVEN(edge_count) */)
    {
        return counter_value < 1300;
    }

    return false;
}
