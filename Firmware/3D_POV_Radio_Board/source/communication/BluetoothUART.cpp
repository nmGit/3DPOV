/*
 * BluetoothUART.cpp
 *
 *  Created on: Apr 12, 2019
 *      Author: Cassidy
 */

#include "BluetoothUART.h"


/**
 * Bluetooth UART wrapper for writing an 8-bit integer array.
 */
void bt_uart_write(const uint8_t * buf, unsigned len)
{
    // GPIO9 must be held high on RN52 to send data. This connects to P2.1 on MSP.
    P2->SEL0 &= ~BIT1;  // Clear P2.1
    P2->SEL1 &= ~BIT1;  // SEL1 and SEL0 combined for 00b, for GPIO
    P2->DIR |= BIT1;    // Configure the port as output (Pg 696 MSP432 user guide)
    P2->OUT |= BIT1;   // Drive the output of this pin high (Pg 696 MSP432 user guide)

    for(int val = 0; val < len; val++)
    {
        put_val_bt(buf[val]);
    }
}


// buf: buffer to read into
// len: length of buffer (exceeding this would be out of bounds for the buffer)
// returns: Number of characters received
unsigned bt_uart_read(uint8_t * buf, unsigned len)
{
    unsigned pos = 0;
    while(pos == 0 || (buf[pos - 1] != '\r' && pos < len))
    {

        buf[pos] = get_val_bt();
        if(buf[pos] == '\0')
        {
            break;
        }
        pos++;
    }
    buf[pos] = '\0'; // Null terminate that shit
    return pos;
}

static char rx_val; // 8-bit integer value being stored as char
char get_val_bt()
{
    if(uart_a_getc(EUSCI_A1, &rx_val))
    {
       // printf("Received: %c\n",rx_val);
        return rx_val;
    }
    else
    {
        return '\0';
    }
}

void put_val_bt(uint8_t val) {
    uart_a_submit_for_transmit(EUSCI_A1, val);
}




