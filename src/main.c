#include "hw.h"

void handle_usart_recv(void) {
    char recvd = usart_read(MORT_USART);
    if (recvd == '\r') { usart_printf(MORT_USART, "$ "); }

    io_toggle(MORT_DEBUG_LED);
}

int main(void) {
    hw_init();

    usart_register_callback(MORT_USART, handle_usart_recv);

    usart_printf(MORT_USART, "Welcome to MORT\n$ ");

    while (1) {}

    return 0;
}
