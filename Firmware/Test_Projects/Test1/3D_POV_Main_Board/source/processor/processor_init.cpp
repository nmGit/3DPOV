/*
 * processor_init.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */
#include "processor/processor_init.h"
void disable_wdt()
{
    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
            WDT_A_CTL_HOLD;
}
void processor_init()
{
    disable_wdt();
}


