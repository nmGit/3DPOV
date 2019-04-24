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

MotorThread * motorthread;

MotorThread::MotorThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void MotorThread::setSpeed(uint16_t spd)
{
    goal = spd;
}
void MotorThread::Task()
{
    dbg_printf("In Motor Thread\r\n");

    uint16_t var;


    dbg_printf("Motor at %d percent power\n", 0);

    PALDelay_ms(1000);
    pct_pwr_esc(0);
    PALDelay_ms(5000);

    while(1){
        if(goal != curr)
        {
            dbg_printf("goal: %d, curr: %d\n", goal, curr);
            if(curr < goal)
            {
                curr++;
            }else if(curr > goal)
            {
                curr--;
            }
            PALDelay_ms(100);
            pct_pwr_esc(curr);
        }
        PALDelay_ms(200);
#ifdef NAM
        for (var = 0; var < 20; ++var) {
            PALDelay_ms(250);
            pct_pwr++;
            pct_pwr_esc(pct_pwr);
            //dbg_printf("Motor at %d percent power\n", pct_pwr);
        }
        for (var = 0; var < 20; ++var) {
            PALDelay_ms(250);
            pct_pwr--;
            pct_pwr_esc(pct_pwr);
          //  dbg_printf("Motor at %d percent power\n", pct_pwr);
        }
        //dbg_printf("Motor at %d percent power\n", pct_pwr);
        PALDelay_ms(5000);
#endif //NAM
    }
}
