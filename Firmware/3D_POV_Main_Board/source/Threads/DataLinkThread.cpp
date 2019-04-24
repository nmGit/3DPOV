/*
 * DataLinkThread.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: Noah
 */

#include "Threads/DataLinkThread.h"
#include "DebugUART.h"
#include "PAL/PALQueue.h"

PALQueue * computer_tx_queue;
PALQueue * computer_rx_queue;
PALSemaphore * dbg_msg_mutex;
DataLinkThread::DataLinkThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{
    computer_tx_queue = new PALQueue(0x30, sizeof(char));
    computer_rx_queue = new PALQueue(0x80, sizeof(char));
    dbg_msg_mutex = new PALSemaphore(true);
}

void DataLinkThread::Task()
{
   // dbg_printf("In Data Link Thread\r\n");
    char chr;
    while(1)
    {
        computer_tx_queue->get(&chr);
        putc_dbg(chr);
    }
}
