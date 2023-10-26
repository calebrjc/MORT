#ifndef _CALEBRJC_BSP_DRIVERS_USART_H_
#define _CALEBRJC_BSP_DRIVERS_USART_H_

#include <stdbool.h>

#include "bsp/hw_defs.h"

/// @brief Baud rates for the USART.
typedef enum usart_baud_rate {
    USART_BAUD_INVALID = 0U,
    USART_BAUD_9600    = 9600U,
    USART_BAUD_19200   = 19200U,
    USART_BAUD_38400   = 38400U,
    USART_BAUD_57600   = 57600U,
    USART_BAUD_115200  = 115200U,
} usart_baud_rate;

/// @brief Configuration for the USART.
typedef struct usart_config {
    /// @brief The baud rate to use.
    usart_baud_rate baud_rate;

    /// @brief Whether or not to echo received characters.
    bool echo_on_recv;
} usart_config;

/// @brief A callback to be called when a character is received.
typedef void (*usart_recv_callback)(char);

/// @brief Initialize the USART.
/// @param device The USART to initialize.
/// @param config The configuration to use.
void usart_init(usart device, usart_config config);

/// @brief Return true if the USART has a character to read.
/// @param device The USART to check.
/// @return True if the USART has a character to read.
bool usart_poll(usart device);

/// @brief Return a character read from the USART.
/// @param device The USART to read from.
/// @return A character read the from USART.
char usart_read(usart device);

/// @brief Write a character to the USART.
/// @param device The USART to write to.
/// @param c The character to write to the USART.
void usart_write(usart device, char c);

/// @brief Register a callback to be called when a character is received.
/// @param device The USART to register the callback for.
/// @param callback The callback to register.
void usart_register_callback(usart device, usart_recv_callback on_character_recv);

#endif  // _CALEBRJC_BSP_DRIVERS_USART_H_