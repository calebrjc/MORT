#include "hw.h"

#include <avr/interrupt.h>

void hw_init(void) {
    // Initialize IO pins
    io_configure(
        MORT_DEBUG_LED, (io_config){.direction = IO_DIRECTION_OUTPUT, .initial_level = IO_HIGH});

    // Initialize the USART
    usart_init(MORT_USART, (usart_config){.baud_rate = USART_BAUD_57600, .echo_on_recv = true});

    // Enable interrupts
    sei();
}
