/*
 * MainThread.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include "Threads/MainThread.h"
#include "Threads/ComputerInterfaceThread.h"
#include "PAL/PALControl.h"
#include "DebugUART.h"

ComputerInterfaceThread::ComputerInterfaceThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
void ComputerInterfaceThread::Task()
{
    dbg_printf("In Computer Interface Thread\r\n");


    while(1){
        PALYield();
    }
}


