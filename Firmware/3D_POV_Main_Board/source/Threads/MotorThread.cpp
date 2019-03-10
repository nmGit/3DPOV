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
MotorThread::MotorThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void MotorThread::Task()
{
    dbg_printf("In Motor Thread\r\n");

    while(1){
        PALYield();
    }
}
