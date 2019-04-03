/*
 * PWM.h
 *
 *  Created on: Mar 10, 2019
 *      Author: Joe Sender
 */

#ifndef SOURCE_PWM_PWM_H_
#define SOURCE_PWM_PWM_H_


#include <stdint.h>
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "platform/platform_init.h"

void pwm_init(void);

uint8_t set_duty(uint16_t duty);



#endif /* SOURCE_PWM_PWM_H_ */
