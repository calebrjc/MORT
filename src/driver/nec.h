#pragma once

#include "util/stdinc.h"

// NOTE(Caleb):
// These keycodes are based on Adafruit's NEC IR remote, which was used for this build.
// https://www.adafruit.com/product/389
typedef enum
{
    MORT_NEC_BTN_NONE      = 0xFF,
    MORT_NEC_BTN_VOLN      = 0x00,
    MORT_NEC_BTN_PLAYPAUSE = 0x01,
    MORT_NEC_BTN_VOLP      = 0x02,
    MORT_NEC_BTN_SETUP     = 0x04,
    MORT_NEC_BTN_UP        = 0x05,
    MORT_NEC_BTN_STOPMODE  = 0x06,
    MORT_NEC_BTN_LEFT      = 0x08,
    MORT_NEC_BTN_ENTERSAVE = 0x09,
    MORT_NEC_BTN_RIGHT     = 0x0A,
    MORT_NEC_BTN_010P      = 0x0C,
    MORT_NEC_BTN_DOWN      = 0x0D,
    MORT_NEC_BTN_BACK      = 0x0E,
    MORT_NEC_BTN_1         = 0x10,
    MORT_NEC_BTN_2         = 0x11,
    MORT_NEC_BTN_3         = 0x12,
    MORT_NEC_BTN_4         = 0x14,
    MORT_NEC_BTN_5         = 0x15,
    MORT_NEC_BTN_6         = 0x16,
    MORT_NEC_BTN_7         = 0x18,
    MORT_NEC_BTN_8         = 0x19,
    MORT_NEC_BTN_9         = 0x1A,
    MORT_NEC_BTN_MAX,
} mort_nec_button_e;

typedef void (*mort_nec_on_data_recv_cb)(mort_nec_button_e data);

void mort_nec_set_callback(mort_nec_on_data_recv_cb cb);

const char *mort_nec_button_to_string(mort_nec_button_e button);

void mort_nec_on_falling_edge(void);
void mort_nec_on_counter_overflow(void);
