#include <avr/interrupt.h>
#include <stddef.h>
#include <util/delay.h>

#include "bsp/io/io.h"
#include "bsp/usart/usart.h"

void toggle_pb0(char c) {
    (void)c;

    io_toggle(BSP_PB0);
}

void write_string(const char *s, size_t size) {
    for (size_t i = 0; i < size; i++) { usart_write(BSP_USART0, s[i]); }
}

int main(void) {
    sei();

    io_configure(BSP_PB0, (io_config){.direction = IO_OUTPUT, .initial_level = IO_HIGH});

    usart_init(BSP_USART0, (usart_config){.baud_rate = USART_BAUD_57600, .echo_on_recv = true});
    usart_printf(BSP_USART0, "Welcome to MORT\n> ");
    usart_register_callback(BSP_USART0, toggle_pb0);

    while (1) {
        // TODO(Caleb): Refactor test code into a test module?
        // PB5 = PB1
        // io_write(IO_PB5, io_read(IO_PB1));

        //    io_toggle(PB0);

        // if (usart_poll()) {
        //     char c = usart_read();

        //     if (c == '1') {
        //         io_write(IO_PB0, IO_HIGH);
        //     } else if (c == '0') {
        //         io_write(IO_PB0, IO_LOW);
        //     }

        //     usart_write(c);

        //     if (c == '\r') { usart_write('\n'); }
        // }

        // _delay_ms(500);
    }

    return 0;
}
