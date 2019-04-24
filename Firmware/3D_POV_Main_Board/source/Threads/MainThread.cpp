/*
 * MainThread.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include <string.h>
#include "Threads/MainThread.h"
#include "Threads/MotorThread.h"
#include "Threads/RadioInterfaceThread.h"
#include "Threads/ComputerInterfaceThread.h"
#include "Threads/DataLinkThread.h"
#include "PAL/PALControl.h"
#include "platform/platform_init.h"
#include "DebugUART.h"

MainThread::MainThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}
extern MotorThread * motorthread;
void MainThread::Task()
{

    DataLinkThread * dataLinkThread = new DataLinkThread(4, 0x500, "Datalink Thread");
    dataLinkThread->Start();

    print_init_message();

    dbg_printf("In Main Thread\r\n");

    //RadioThread * radioThread = new RadioThread(3, 0x500, "Radio Thread");
    //radioThread->Start();

    motorthread = new MotorThread(3, 0x500, "Motor Thread");
    motorthread->Start();

    ComputerInterfaceThread * computerthread = new ComputerInterfaceThread(5, 0x800, "Computer Thread");
    computerthread->Start();
    while(1){
        PALYield();
    }
}


