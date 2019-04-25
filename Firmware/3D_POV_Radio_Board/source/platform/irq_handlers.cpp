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
#include "HALL/hall.h"

//*****************************************************************************
// SysTick Handler
//*****************************************************************************
extern "C" void SysTick_Handler(void) {
//    printf("\nCurrent value: %d\n", SysTick_getValue());
    wrap_count = wrap_count + 1;
}

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

//*****************************************************************************
// GPIO Port 1 Handler
//*****************************************************************************
void PORT1_IRQHandler() {
    uint32_t temp_ticks = SysTick_getValue();
    hall_trig = true;
    rev_ticks = (wrap_count * wrap_period) + temp_ticks - old_ticks;
    old_ticks = temp_ticks;

    P1->IFG &= ~BIT0; // Clear interrupt
}
