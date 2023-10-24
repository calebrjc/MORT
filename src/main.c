#include <util/delay.h>

#include "bsp/io/io.h"

int main(void) {
    io_configure(IO_PB0, (io_config){.direction = IO_OUTPUT, .initial_level = IO_HIGH});
    io_configure(IO_PB5, (io_config){.direction = IO_OUTPUT, .initial_level = IO_LOW});
    io_configure(IO_PB1, (io_config){.direction = IO_INPUT, .resistor = IO_PULLUP});

    while (1) {
        // PB5 = PB1
        io_write(IO_PB5, io_read(IO_PB1));

        io_toggle(IO_PB0);
        
        _delay_ms(500);
    }

    return 0;
}
