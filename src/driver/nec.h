#pragma once

#include "hal/counter.h"
#include "hal/gpio.h"
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

/// @brief A function which is called when NEC data is received.
/// @param [in] data The command that was received.
typedef void (*mort_nec_on_data_recv_cb)(mort_nec_button_e data);

/// @brief Initialize the NEC driver.
/// @param [in] pin The pin to use for the NEC receiver.
/// @param [in] counter The counter to use for timing.
/// @param [in] on_data_recv Required; The function to call when NEC data is received.
/// @retval 0 if the operation was successful.
/// @retval -EIO if a peripheral error occurred.
/// @retval -EINVAL if any of the parameters are invalid.
int mort_nec_init(
    mort_gpio_pin_e pin, mort_counter_e counter, mort_nec_on_data_recv_cb on_data_recv);

/// @brief Set the function to call when NEC data is received.
/// @param [in] cb The function to call when NEC data is received.
void mort_nec_set_callback(mort_nec_on_data_recv_cb cb);

/// @brief Convert a button code to a string.
/// @param [in] button The button code to convert.
/// @return The string representation of the button code.
const char *mort_nec_button_to_string(mort_nec_button_e button);
