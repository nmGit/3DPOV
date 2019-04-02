/*
 * UART.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */
#include "ti/devices/msp432p4xx/inc/msp.h"

#include "UART.h"
#include <stdint.h>
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

// Using externs is not great style, whaddyagonnado?
extern char uart_a_0_rcvd_chr;
static PALSemaphore uart_a_mutex = PALSemaphore();

void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr)
{
    // Bases: EUSCI_A0
    // Check if the TX buffer is empty first
    while(!(base->IFG & EUSCI_A_IFG_TXIFG));
    base->TXBUF = chr;
}

uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms)
{
    if(base == EUSCI_A0)
    {
        // Wait for 100 ms for a character
        if(uart_a_mutex.tryTake(timeout_ms))
        {

            // Block until we receive a character
            // the semaphore will be available if we have received a character
            // and it hasn't been received

            *c = uart_a_0_rcvd_chr;

            return 1;
        }

        // If no character is received then return 0.
        return 0;
    }

    return 0;
}

char uart_a_0_ISR()
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
     {
         // Check if the TX buffer is empty first
         while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

         // Save the received character
         uart_a_0_rcvd_chr =  EUSCI_A0->RXBUF;

         // Echo the received character back
         //EUSCI_A0->TXBUF = uart_a_0_rcvd_chr;

         uart_a_mutex.give();
     }
    return 0;
}
