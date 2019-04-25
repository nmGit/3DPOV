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
#include "stdio.h"
// Radio Bluetooth UART is EUSCI_A1
// P2.2, P2.3

// Using externs is not great style, whaddyagonnado?
extern char uart_a_1_rcvd_chr;

static volatile bool done_transmitting = true;
static bool rxbuf_rdy = false;

static uint8_t rx_buf[RX_BUF_SIZE];
static unsigned rx_buf_head = 0;
static unsigned rx_buf_tail = 0;

void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr)
{
    // Base: EUSCI_A1
    // Check if the TX buffer is empty first
    //while(!(base->IFG & EUSCI_A_IFG_TXIFG));
    while(!done_transmitting);
    done_transmitting = false;
    base->TXBUF = chr;

}

unsigned num_rx_buffer_elements()
{
    unsigned size = rx_buf_tail > rx_buf_head ?
            (RX_BUF_SIZE - rx_buf_head + rx_buf_tail + 1) :
            (rx_buf_head - rx_buf_tail + 1);
    return size;
}




/*
 * Returns false if buffer is full.
 * Otherwise, puts character into buffer at rx_buf[rx_buf_head] and returns true.
 */
bool rx_buf_push(char character) {

    if (rx_buf_head == (rx_buf_tail-1)%RX_BUF_SIZE) {
        // Buffer is full
        return false;
    } else {
        rx_buf[rx_buf_head] = character;
        rx_buf_head++;
        rx_buf_head %= RX_BUF_SIZE;
    }

    return true;

}

/*
 * If the buffer is empty, returns false.
 * Otherwise, puts the character at rx_buf[rx_buf_tail] into
 * character pointer and returns true.
 */
bool rx_buf_pop(char* character) {

    if (rx_buf_tail == (rx_buf_head-1)%RX_BUF_SIZE) {
        // Buffer is empty
        *character = 0;
        return false;
    } else {
        *character = rx_buf[rx_buf_tail];
        rx_buf_tail++;
        rx_buf_tail %= RX_BUF_SIZE;
    }

    return true;

}

/*
 * Reads up until a newline
 */
bool read_line(char* buffer, unsigned max_len) {

    // Check if there is even a newline present
    bool has_newline = false;
    unsigned num_elems = num_rx_buffer_elements();

    unsigned curr = rx_buf_tail;

    while(curr < num_elems)
    {

        if(rx_buf[curr] == '\r')
        {
            has_newline = true;
            break;
        }
        curr++;
        curr %= RX_BUF_SIZE;
    }

    if(!has_newline)
    {
       return false;
    }

    curr = rx_buf_tail;
    unsigned index = 0;
    while(buffer[index] != '\n' && index < num_elems && index < max_len)
    {
        rx_buf_pop(&buffer[index]);
        index++;
    }

     return true;


}
uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms)
{

    if(base == EUSCI_A1) // EUSCI_A1 used for bluetooth RX/TX on radio board
    {
        rx_buf_pop(c);
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
         rx_buf_push(uart_a_1_rcvd_chr);
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
