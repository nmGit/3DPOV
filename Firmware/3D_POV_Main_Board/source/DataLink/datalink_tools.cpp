/*
 * datalink_tools.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: Noah
 */
#include "PAL/PALQueue.h"

extern PALQueue * computer_tx_queue;

void submit_for_transmit_to_computer(const char * buf, unsigned len, unsigned timeout_ms)
{
    for(unsigned chr = 0; chr < len; chr ++)
    {
        computer_tx_queue->add((void *)(&(buf[chr])), timeout_ms);

    }
}



