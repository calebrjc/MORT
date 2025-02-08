#pragma once

// NOTE(Caleb):
// The names for these keycodes are based on Adafruit's NEC IR remote, which was used for this build.
// TODO(Caleb): Link the remote
// TODO(Caleb): Confirm the values of these keycodes
typedef enum
{
	MORT_NEX_BTN_NONE = 0,
	MORT_NEC_BTN_VOLN = 0, 
	MORT_NEC_BTN_PLAYPAUSE,
	MORT_NEC_BTN_VOLP,
	MORT_NEC_BTN_SETUP,
	MORT_NEC_BTN_UP,
	MORT_NEC_BTN_STOPMODE,
	MORT_NEC_BTN_LEFT,
	MORT_NEC_BTN_ENTERSAVE,
	MORT_NEC_BTN_RIGHT,
	MORT_NEC_BTN_010P,
	MORT_NEC_BTN_DOWN,
	MORT_NEC_BTN_BACK,
	MORT_NEC_BTN_1,
	MORT_NEC_BTN_2,
	MORT_NEC_BTN_3,
	MORT_NEC_BTN_4,
	MORT_NEC_BTN_5,
	MORT_NEC_BTN_6,
	MORT_NEC_BTN_7,
	MORT_NEC_BTN_8,
	MORT_NEC_BTN_9,
} mort_nec_button_e;

/// @brief Initialize the NEC IR driver.
/// @return 0 if successful, or -1 if an error occurred.
int mort_nec_init(void);

/// @brief Run the interrupt handler for the NEC IR driver.
void mort_nec_on_falling_edge(void);

