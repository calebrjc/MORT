#ifndef _CALEBRJC_BSP_IO_IO_H_
#define _CALEBRJC_BSP_IO_IO_H_

#include "pins.h"

/// @brief The logic level of an IO pin.
typedef enum io_logic_level {
    /// @brief Represents a logic low.
    IO_LOW,

    /// @brief Represents a logic high.
    IO_HIGH,
} io_logic_level;

/// @brief The direction of an IO pin.
typedef enum io_direction {
    /// @brief Represents an input pin.
    IO_INPUT,

    /// @brief Represents an output pin.
    IO_OUTPUT,
} io_direction;

/// @brief The resistor configuration of an IO pin.
typedef enum io_resistor {
    /// @brief Represents a floating pin.
    IO_FLOATING,

    /// @brief Represents a pulled up pin.
    IO_PULLUP,
} io_resistor;

/// @brief The configuration of an IO pin.
typedef struct io_config {
    /// @brief The direction of the pin.
    io_direction direction;

    /// @brief Whether the pin is pulled up or not.
    io_resistor resistor;

    /// @brief The initial logic level of the pin.
    io_logic_level initial_level;
} io_config;

/// @brief Initialize the IO module.
void io_init(void);

/// @brief Configure an IO pin.
/// @param pin The pin to configure.
/// @param config The configuration to apply to the pin.
void io_configure(io_pin pin, io_config config);

/// @brief Return the logic level of an IO pin.
/// @param pin The pin to read.
/// @return The logic level of an IO pin.
io_logic_level io_read(io_pin pin);

/// @brief Write a logic level to an IO pin.
/// @param pin The pin to write to.
/// @param level The logic level to write.
void io_write(io_pin pin, io_logic_level level);

/// @brief Toggle the logic level of an IO pin.
/// @param pin The pin to toggle.
void io_toggle(io_pin pin);

#endif  // _CALEBRJC_BSP_IO_IO_H_
