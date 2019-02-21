/*
 * UART.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */
#include "ti/devices/msp432p4xx/inc/msp.h"

#include "UART.h"
// backchannel uart is eUSCI_A0
// P1.2, P1.3
//void uart_init()
/*
void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        // Check if the TX buffer is empty first
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

        // Echo the received character back
        EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
    }
}
*/
static char uart_a_0_rcvd_chr;

void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr)
{
    // Bases: EUSCI_A0
    // Check if the TX buffer is empty first
    while(!(base->IFG & EUSCI_A_IFG_TXIFG));
    base->TXBUF = chr;
}

char uart_a_getc(EUSCI_A_Type * base)
{
    if(base == EUSCI_A0)
    {
        return uart_a_0_rcvd_chr;
    }
}

char uart_a_0_ISR()
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
     {
         // Check if the TX buffer is empty first
         while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

         // Echo the received character back
         EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
     }
}
