/*
 * ESC.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Joe Sender
 */

#include "ESC.h"

uint8_t pct_pwr_esc(uint16_t duty){

    uint16_t outDuty, interm;
    interm = duty%100;                     // Put duty withing 0-99%
    outDuty = (interm*ESC_ZERO_PCT_PWR/100) + ESC_ZERO_PCT_PWR;
    //dbg_printf("\rUsing duty cycle:%d", outDuty);

    outDuty = set_duty(outDuty);
    return duty;

}

