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
#include "FreeRTOS.h"
#include "Devices/ESC/ESC.h"

MotorThread::MotorThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void MotorThread::Task()
{
    dbg_printf("In Motor Thread\r\n");

    PALYield();

    uint16_t var;
    uint16_t pct_pwr = 0;

    dbg_printf("\rMotor at %d percent power", pct_pwr);

    vTaskDelay(1000);
    pct_pwr = pct_pwr_esc(pct_pwr);
    vTaskDelay(5000);

    while(1){
        for (var = 0; var < 15; ++var) {
            vTaskDelay(250);
            pct_pwr++;
            pct_pwr_esc(pct_pwr);
            dbg_printf("\rMotor at %d percent power", pct_pwr);
        }
        for (var = 0; var < 15; ++var) {
            vTaskDelay(250);
            pct_pwr--;
            pct_pwr_esc(pct_pwr);
            dbg_printf("\rMotor at %d percent power", pct_pwr);
        }
        dbg_printf("\rMotor at %d percent power", pct_pwr);
        vTaskDelay(5000);
        PALYield();
    }
}
