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
#include "PAL/PALDelay.h"
#include "DebugUART.h"
#include "platform/platform_init.h"
#include <cstring>

#define COMPUTER_INTERFACE_RX_BUF_LEN 256

ComputerInterfaceThread::ComputerInterfaceThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}

char rxBuf[COMPUTER_INTERFACE_RX_BUF_LEN] = {0};

void ComputerInterfaceThread::Task()
{
    dbg_printf("In Computer Interface Thread\r\n");

    unsigned CIT_counter = 0;
    char identify_string[] = "*IDN?\r";
    unsigned identify_string_len = strlen(identify_string);

    while(1){

        CIT_counter++;

        dbg_readLine(rxBuf, COMPUTER_INTERFACE_RX_BUF_LEN);

        //printf("recieved: %s\r\n", rxBuf);
        if(strncmp(rxBuf, identify_string, identify_string_len) == 0)
        {

            dbg_printf("3DPOV\r\n");
            PALDelay_ms(1000);
            print_init_message();
        }else
        {
            //dbg_printf("CIT count: %d\r\n", CIT_counter);
            PALDelay_ms(1000);
        }
    }
}


