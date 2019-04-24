/*
 * MainThread.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include "Threads/MainThread.h"
#include "Threads/MotorThread.h"
#include "Threads/ComputerInterfaceThread.h"
#include "PAL/PALControl.h"
#include "PAL/PALDelay.h"
#include "DebugUART.h"
#include "platform/platform_init.h"
#include "DataLink/data_packing.h"
#include <cstring>

#define COMPUTER_INTERFACE_RX_BUF_LEN 256

ComputerInterfaceThread::ComputerInterfaceThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}

char rxBuf[COMPUTER_INTERFACE_RX_BUF_LEN] = {0};
extern MotorThread * motorthread;
void ComputerInterfaceThread::Task()
{
    dbg_printf("In Computer Interface Thread\r\n");

    unsigned CIT_counter = 0;
    char identify_string[] = "*IDN?\r\n";
    unsigned identify_string_len = strlen(identify_string);

    const char mtr_spd_header[] = "SPD";
    unsigned mtr_spd_header_len = strlen(mtr_spd_header);

    while(1){

        CIT_counter++;

        dbg_readLine(rxBuf, COMPUTER_INTERFACE_RX_BUF_LEN);

        if(strncmp(rxBuf, identify_string, identify_string_len) == 0)
        {

            dbg_printf("3DPOV\r\n");
            PALDelay_ms(1000);
            print_init_message();

        }else if(strncmp(rxBuf, mtr_spd_header, mtr_spd_header_len) == 0)
        {
            memcpy(&mtr_spd_packet, rxBuf, sizeof(mtr_spd_packet_t));
            //printf("new speed: %d\n", mtr_spd_packet.value);
            dbg_printf("Speed: %d\n", mtr_spd_packet.value);
            motorthread->setSpeed((uint16_t)mtr_spd_packet.value);

        }
        else
        {
            //printf("%s unrecognized\n", rxBuf);
            dbg_printf("ERROR: Unrecognized Command: %s\n", rxBuf);
        }
    }
}


