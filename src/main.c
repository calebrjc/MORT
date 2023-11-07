#include <avr/interrupt.h>

#include "bsp/usart/usart.h"

int main(void) {
    sei();

    usart_init(BSP_USART0, (usart_config){.baud_rate = USART_BAUD_57600, .echo_on_recv = true});
    usart_printf(BSP_USART0, "Welcome to MORT\n> ");

    while (1) {}

    return 0;
}
