/*
 * MainThread.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include "Threads/MainThread.h"
#include "Threads/RadioInterfaceThread.h"
#include "PAL/PALControl.h"
#include "DebugUART.h"

RadioThread::RadioThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void RadioThread::Task()
{
    dbg_printf("In Radio Thread\r\n");

    while(1){
        PALYield();
    }
}


