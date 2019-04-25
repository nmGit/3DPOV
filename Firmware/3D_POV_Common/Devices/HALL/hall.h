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
bool hall_trig;             // Set to true when GPIO interrupt triggered
                            // set to false when read and initialized
uint32_t old_ticks;        // Hall current tick value (NOT number of ticks per revolution)
uint32_t wrap_count;        // Number of SysTick wraps before GPIO interrupt is triggered
uint32_t wrap_period;       // SysTick period
uint32_t rev_ticks;         // Ticks per revolution

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void hallInit(void);
