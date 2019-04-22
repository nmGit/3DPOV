/*
 * irq_handlers.cpp
 *
 *  Created on: April 12, 2019
 *      Author: Cassidy
 */

#include <stdio.h>
#include "irq_handlers.h"
#include "ti/devices/msp432p4xx/inc/msp.h"
#include "UART/RadioUART.h"
#include "SPI/spi.h"



//*****************************************************************************
// General IRQ A Handler
//*****************************************************************************
void EUSCIAX_IRQHandler(void) {
    EUSCI_A_SPI_Type* spi_struct = (EUSCI_A_SPI_Type*) base;

    // Set trx_rdy to true
    tx_rdy = 1;

    // Clear the transmit interrupt flag
    spi_struct->IFG &= ~EUSCI_B_IFG_TXIFG0;

}

//*****************************************************************************
// General IRQ B Handler
//*****************************************************************************
void EUSCIBX_IRQHandler(void) {
    EUSCI_B_SPI_Type* spi_struct = (EUSCI_B_SPI_Type*) base;

    // Set trx_rdy to true
    tx_rdy = 1;

    // Clear the transmit interrupt flag
    spi_struct->IFG &= ~EUSCI_B_IFG_TXIFG0;

}

//*****************************************************************************
// EUSCI type A Handlers
//*****************************************************************************

extern "C" void EUSCIA0_IRQHandler(void)
{
    printf("SHIT! Wrong handler (0, you dumbass)\r\n");
}

extern "C" void EUSCIA1_IRQHandler(void)
{
    // Bluetooth
    uart_a_1_ISR();
    EUSCIAX_IRQHandler();
}

extern "C" void EUSCIA2_IRQHandler(void)
{
    printf("SHIT! Wrong handler (2, you dumbass)\r\n");
}

extern "C" void EUSCIA3_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

//*****************************************************************************
// EUSCI type B Handlers
//*****************************************************************************
extern "C" void EUSCIB0_IRQHandler(void) {
    // SPI
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB1_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB2_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB3_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}
