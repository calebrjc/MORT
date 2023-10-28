#include "bsp/usart/usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "bsp/dsa/queue.h"
#include "bsp/io/io.h"
#include "printf.h"

#ifndef F_CPU
#error "F_CPU must be defined to use the USART driver."
#endif

// Note:
// Although the interface is designed in a generic way to support multiple USART peripherals, this
// implementation only supports one USART peripheral (USART0) on the ATmega328P, because that is the
// only USART peripheral on the microcontroller. Because of this, variables and registers are
// referenced directly instead of some other mechanism (e.g. an array of registers, switch
// statements, and/or macros) to avoid unnecessary overhead and complexity.

// Baud rate calculation macros
#define UBRR(baud)  ((F_CPU / (16UL * baud)) - 1)
#define UBRRH(baud) ((uint8_t)(UBRR(baud) >> 8))
#define UBRRL(baud) ((uint8_t)UBRR(baud))

// Configuration(s) --------------------------------------------------------------------------------

// USART0 configuration (initialized in usart_init())
static usart_config usart0_config = {0};

// USART0 callback function (initialized in usart_register_callback())
static usart_recv_callback usart0_callback = NULL;

// RX and TX Buffers -------------------------------------------------------------------------------

#define USART0_BUFFER_SIZE 16

static uint8_t usart0_rx_buffer[USART0_BUFFER_SIZE];
static queue usart0_rx_queue;

static uint8_t usart0_tx_buffer[USART0_BUFFER_SIZE];
static volatile queue usart0_tx_queue;

// Interrupt handlers ------------------------------------------------------------------------------

/// @brief Data register empty interrupt handler for USART0. Triggered when the USART0 data register
///        is empty and ready to receive more data.
ISR(USART_UDRE_vect) {
    if (!q_is_empty(&usart0_tx_queue)) {
        // Send the next byte in the TX buffer
        UDR0 = q_dequeue(&usart0_tx_queue);
    } else {
        // Nothing to send, disable data register empty interrupts
        UCSR0B &= ~_BV(UDRIE0);
    }
}

/// @brief Receive complete interrupt handler for USART0.
ISR(USART_RX_vect) {
    // Read the byte from the data register
    uint8_t data = UDR0;

    // Ignore the byte if the RX buffer is full
    if (q_is_full(&usart0_rx_queue)) return;

    if (usart0_config.echo_on_recv) {
        // Echo the byte back to the sender
        // (Convert carriage returns to newlines)
        usart_write(BSP_USART0, ((char)data == '\r') ? '\n' : (char)data);
    }

    // Enqueue the byte into the RX buffer
    q_enqueue(&usart0_rx_queue, data);

    // Call the callback function if there is one registered
    if (usart0_callback) { usart0_callback((char)data); }
}

// Implementation ----------------------------------------------------------------------------------

void usart_init(usart device, usart_config config) {
    // TODO(Caleb): Support other data lengths and parity modes
    (void)device;

    // Set baud rate
    UBRR0H = (uint8_t)UBRRH(config.baud_rate);
    UBRR0L = (uint8_t)UBRRL(config.baud_rate);

    // Enable receiver and transmitter
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    // Set frame format: 8data, 1stop bit
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

    // Initialize ring buffers
    q_init(&usart0_rx_queue, usart0_rx_buffer, sizeof(usart0_rx_buffer));
    q_init(&usart0_tx_queue, usart0_tx_buffer, sizeof(usart0_tx_buffer));

    // Save the configuration
    usart0_config = config;

    // Clear RX and TX interrupt flags
    UCSR0A |= _BV(RXC0);

    // Enable RX and TX interrupts
    UCSR0B |= _BV(RXCIE0);
}

bool usart_poll(usart device) {
    (void)device;

    // Return true if there is data in the RX buffer
    return !q_is_empty(&usart0_rx_queue);
}

char usart_read(usart device) {
    (void)device;

    // Spin until there is data in the RX buffer
    while (q_is_empty(&usart0_rx_queue)) {}

    return (char)q_dequeue(&usart0_rx_queue);
}

void usart_write(usart device, char c) {
    (void)device;

    if (c == '\n') {
        // Send a carriage return before the newline (for terminals that require it)
        usart_write(BSP_USART0, '\r');
    }

    // Spin until there is space in the TX buffer
    while (q_is_full(&usart0_tx_queue)) {}

    // Enqueue the byte in the TX buffer
    q_enqueue(&usart0_tx_queue, c);

    // Enable TX interrupts
    UCSR0B |= _BV(UDRIE0);
}

void _putchar(char c) {
    usart_write(BSP_USART0, c);
}

void usart_printf(usart device, const char* format, ...) {
    (void)device;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void usart_register_callback(usart device, usart_recv_callback on_character_recv) {
    (void)device;

    usart0_callback = on_character_recv;
}
