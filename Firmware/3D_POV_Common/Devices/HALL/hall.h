/******************************************************************************
 * FILE:            hall.h                                                    *
 * AUTHOR:          Joe Sender                                                *
 * DATE CREATED:    4/25/2019                                                 *
 *                                                                            *
 *****************************************************************************/

#include <stdint.h>

//*****************************************************************************
// Globals
//*****************************************************************************
volatile bool hall_trig;             // Set to true when GPIO interrupt triggered
                            // set to false when read and initialized
volatile uint32_t wrap_count;        // Number of SysTick wraps before GPIO interrupt is triggered
volatile uint32_t rev_ticks;         // Ticks per revolution

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void hallInit(void);
