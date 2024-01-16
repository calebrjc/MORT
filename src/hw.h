#ifndef _CALEBRJC_MORT_HW_H_
#define _CALEBRJC_MORT_HW_H_

#include <bsp/io.h>
#include <bsp/usart.h>

#define MORT_USART     BSP_USART0
#define MORT_DEBUG_LED BSP_PB5

/// @brief Initialize MCU hardware and BSP components for MORT.
void hw_init(void);

#endif  // _CALEBRJC_MORT_HW_H_
