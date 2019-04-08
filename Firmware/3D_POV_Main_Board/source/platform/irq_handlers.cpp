/*
 * irq_handlers.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */




#include "irq_handlers.h"
#include "ti/devices/msp432p4xx/inc/msp.h"
#include "UART/UART.h"
#include "SPI/spi.h"
// UART interrupt service routine
extern "C" void EUSCIA0_IRQHandler(void)
{
    uart_a_0_ISR();
    EUSCIAX_IRQHandler();
}

extern "C" void EUSCIA2_IRQHandler(void)
{
    uart_a_2_ISR();
    EUSCIAX_IRQHandler();
}
