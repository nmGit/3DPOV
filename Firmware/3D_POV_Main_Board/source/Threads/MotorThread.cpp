/*
 *  MotorThread.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include "Threads/MainThread.h"
#include "Threads/MotorThread.h"
#include "PAL/PALControl.h"
#include "DebugUART.h"
#include "PWM/PWM.h"
#include "Devices/ESC/ESC.h"
#include "PAL/PALDelay.h"

MotorThread::MotorThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void MotorThread::Task()
{
    dbg_printf("In Motor Thread\r\n");

    uint16_t var;
    uint16_t pct_pwr = 0;

    //dbg_printf("\rMotor at %d percent power", pct_pwr);

    PALDelay_ms(1000);
    pct_pwr = pct_pwr_esc(pct_pwr);
    PALDelay_ms(5000);

    while(1){
        for (var = 0; var < 15; ++var) {
            PALDelay_ms(250);
            pct_pwr++;
            pct_pwr_esc(pct_pwr);
            dbg_printf("\rMotor at %d percent power", pct_pwr);
        }
        for (var = 0; var < 15; ++var) {
            PALDelay_ms(250);
            pct_pwr--;
            pct_pwr_esc(pct_pwr);
            dbg_printf("\rMotor at %d percent power", pct_pwr);
        }
        dbg_printf("\rMotor at %d percent power", pct_pwr);
        PALDelay_ms(5000);
    }
}
