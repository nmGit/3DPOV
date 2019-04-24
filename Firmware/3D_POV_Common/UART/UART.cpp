/*
 * UART.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */
#include "ti/devices/msp432p4xx/inc/msp.h"
#include "PAL/PALQueue.h"
#include "UART.h"
#include <stdio.h>
#include <stdint.h>
// backchannel uart is eUSCI_A0
// P1.2, P1.3

// Using externs is not great style, whaddyagonnado?
extern char uart_a_0_rcvd_chr;
extern char uart_a_2_rcvd_chr;

static PALSemaphore * uart_a_mutex = new PALSemaphore();
extern PALQueue * computer_rx_queue;

#define RX_BUF_SIZE 256
char rx_buffer[RX_BUF_SIZE] = {0};
char head = 0;
char tail = 0;


void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr)
{
    // Bases: EUSCI_A0, EUSCI_A2
    // Check if the TX buffer is empty first
    while(!(base->IFG & EUSCI_A_IFG_TXIFG));
    base->TXBUF = chr;

}

uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms)
{

    if(base == EUSCI_A0) // EUSCI_A0 used for computer interface (i.e. debug)
    {
        // Wait for 100 ms for a character
        //if(uart_a_mutex->tryTake(timeout_ms))
        //{

            // Block until we receive a character
            // the semaphore will be available if we have received a character
            // and it hasn't been received

            //*c = uart_a_0_rcvd_chr;
            computer_rx_queue->get(c, timeout_ms);
#ifdef NAM
            if(tail < head)
            {
                *c = rx_buffer[tail];
                rx_buffer[tail] = 0;
                tail++;
                tail %= RX_BUF_SIZE;
            }
            else
            {
                return 0;
            }
#endif //NAM
            return 1;
        //}

        // If no character is received then return 0.
        return 0;
    }
    else if (base == EUSCI_A2) // EUSCI_A2 used for bluetooth uart
    {
        // Wait for 100 ms for a character
        if(uart_a_mutex->tryTake(timeout_ms)) // NOTE: replace with a boolean!!!
        {

            // Block until we receive a character
            // the semaphore will be available if we have received a character
            // and it hasn't been received

            *c = uart_a_2_rcvd_chr;

            return 1;
        }

        // If no character is received then return 0.
        return 0;
    }

    return 0;
}

// A0 is used by debug UART

char uart_a_0_ISR()
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
     {
         // Check if the TX buffer is empty first
        // while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

         // Save the received character
         uart_a_0_rcvd_chr =  EUSCI_A0->RXBUF;

         if(computer_rx_queue->add(&(uart_a_0_rcvd_chr)) != pdPASS)
         {
             printf("Rx queue add fail\n");
         }

#ifdef NAM
         if(head != tail-1)
         {
             rx_buffer[head] = uart_a_0_rcvd_chr;
             head++;
             head %= RX_BUF_SIZE;
         }
#endif //NAM
         // Echo the received character back
         //EUSCI_A0->TXBUF = uart_a_0_rcvd_chr;

         uart_a_mutex->give();
     }
    return 0;
}

// A2 is used by bluetooth UART
char uart_a_2_ISR()
{

    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG)
     {
         // Check if the TX buffer is empty first
         while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG));

         // Save the received character
         uart_a_2_rcvd_chr =  EUSCI_A2->RXBUF;


         uart_a_mutex->give();


     }
    return 0;
}
