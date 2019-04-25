/******************************************************************************
 * FILE:            hall.cpp                                                  *
 * AUTHOR:          Joe Sender                                                *
 * DATE CREATED:    4/25/2019                                                 *
 *                                                                            *
 *****************************************************************************/

#include "hall.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void hallInit(){
    hall_trig = false;
    old_ticks = SysTick_getValue();
    wrap_period = SysTick_getPeriod();
    rev_ticks = 0;     // Set to 0 until value changed in IRQ

    P1->SEL0 &= ~BIT0;  // SEL0 and SEL1 set to 0 for pin 0
    P1->SEL1 &= ~BIT0;  //  for IO functionality
    P1->DIR  &= ~BIT0;  // Configured for input

    P1->IFG &= ~BIT0;   // Clear interrupt flag
    P1->IES &= ~BIT0;   // Trigger interrupt on rising edge (0->1)
    P1->IE  |= BIT0;    // Interrupt Enable

    MAP_Interrupt_setPriority(INT_PORT1, 0x32);
    MAP_Interrupt_enableInterrupt(INT_PORT1);
}
