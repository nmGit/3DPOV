/*
 * PWM.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: Joe Sender
 */

#include "PWM.h"

void pwm_init(void){
    // Initializing PWM for TIMER_A0 Pin 1 (checked schematic to confirm)
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CAP;    // Set CAP = 0
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_6 // Use Toggle/reset output mode
            | TIMER_A_CCTLN_CCIS__VCC;          // Use CCIxA as input to PWM
    TIMER_A0->CCR[1] = 0x000;                   // Set DUTY to zero
 //   TIMER_A0->CTL &= !TIMER_A_CTL_CLR;
}

uint8_t set_duty(uint16_t duty)
{
    TIMER_A0->CCR[1] = duty;
    return duty;
}


