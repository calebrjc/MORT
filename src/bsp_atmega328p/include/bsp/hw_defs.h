#ifndef _CALEBRJC_BSP_IO_PINS_H_
#define _CALEBRJC_BSP_IO_PINS_H_

#include <stdint.h>

// PIN DEFINITIONS ---------------------------------------------------------------------------------

// Each pin number is an 8-bit integer represented as [XXXPPIII] where:
// - III is the pin index (0-7)
// - PP is the port index (0-2) (B, C, D), and
// - XXX is unused

typedef uint8_t io_pin;

#define BSP_PB0 0x00  // Port B, Pin 0 (0b00000000)
#define BSP_PB1 0x01  // Port B, Pin 1 (0b00000001)
#define BSP_PB2 0x02  // Port B, Pin 2 (0b00000010)
#define BSP_PB3 0x03  // Port B, Pin 3 (0b00000011)
#define BSP_PB4 0x04  // Port B, Pin 4 (0b00000100)
#define BSP_PB5 0x05  // Port B, Pin 5 (0b00000101)
#define BSP_PB6 0x06  // Port B, Pin 6 (0b00000110)
#define BSP_PB7 0x07  // Port B, Pin 7 (0b00000111)

#define BSP_PC0 0x08  // Port C, Pin 0 (0b00001000)
#define BSP_PC1 0x09  // Port C, Pin 1 (0b00001001)
#define BSP_PC2 0x0A  // Port C, Pin 2 (0b00001010)
#define BSP_PC3 0x0B  // Port C, Pin 3 (0b00001011)
#define BSP_PC4 0x0C  // Port C, Pin 4 (0b00001100)
#define BSP_PC5 0x0D  // Port C, Pin 5 (0b00001101)
#define BSP_PC6 0x0E  // Port C, Pin 6 (0b00001110)
#define BSP_PC7 0x0F  // Port C, Pin 7 (0b00001111)

#define BSP_PD0 0x10  // Port D, Pin 0 (0b00010000)
#define BSP_PD1 0x11  // Port D, Pin 1 (0b00010001)
#define BSP_PD2 0x12  // Port D, Pin 2 (0b00010010)
#define BSP_PD3 0x13  // Port D, Pin 3 (0b00010011)
#define BSP_PD4 0x14  // Port D, Pin 4 (0b00010100)
#define BSP_PD5 0x15  // Port D, Pin 5 (0b00010101)
#define BSP_PD6 0x16  // Port D, Pin 6 (0b00010110)
#define BSP_PD7 0x17  // Port D, Pin 7 (0b00010111)

// PERIPHERAL DEFINITIONS --------------------------------------------------------------------------

typedef uint8_t usart;

#define BSP_USART0 0x00  // USART0

#endif  // _CALEBRJC_BSP_IO_PINS_H_
