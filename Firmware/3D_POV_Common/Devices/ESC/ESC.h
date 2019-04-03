/*
 * ESC.h
 *
 *  Created on: Mar 11, 2019
 *      Author: JOE SENDER
 */

#ifndef SOURCE_ESC_ESC_H_
#define SOURCE_ESC_ESC_H_


#include <stdint.h>
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "platform/platform_init.h"
#include "PWM/PWM.h"
#include "DebugUART.h"

uint8_t pct_pwr_esc(uint16_t duty);

#endif /* SOURCE_ESC_ESC_H_ */
