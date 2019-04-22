/*
 * RadioUART.cpp
 *
 *  Created on: April, 2019
 *      Author: Cassidy
 */
#include "ti/devices/msp432p4xx/inc/msp.h"
//#include "PAL/PALQueue.h"
#include "RadioUART.h"
#include <stdint.h>
// Radio Bluetooth UART is EUSCI_A1
// P2.2, P2.3

// Using externs is not great style, whaddyagonnado?
extern char uart_a_1_rcvd_chr;

static volatile bool done_transmitting = true;
static bool rxbuf_rdy = false;
void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr)
{
    // Base: EUSCI_A1
    // Check if the TX buffer is empty first
    //while(!(base->IFG & EUSCI_A_IFG_TXIFG));
    while(!done_transmitting);
    done_transmitting = false;
    base->TXBUF = chr;

}

uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms)
{

    if(base == EUSCI_A1) // EUSCI_A1 used for bluetooth RX/TX on radio board
    {
            while (!rxbuf_rdy);
            *c = uart_a_1_rcvd_chr;
            rxbuf_rdy = false;
            return 1;
    }

        // If no character is received then return 0.
        return 0;

}


// A1 is used by bluetooth UART
char uart_a_1_ISR()
{

    if (EUSCI_A1->IFG & EUSCI_A_IFG_RXIFG)
     {
         EUSCI_A1->IFG &=  ~EUSCI_A_IFG_RXIFG;
         // Save the received character
         uart_a_1_rcvd_chr =  EUSCI_A1->RXBUF;
         rxbuf_rdy = true;
     }
    else if(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG)
    {
        EUSCI_A1->IFG &= ~EUSCI_A_IFG_TXIFG;
        //while(!(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG));
        done_transmitting = true;
    }
    return 0;
}
