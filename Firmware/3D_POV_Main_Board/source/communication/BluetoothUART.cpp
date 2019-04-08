/*
 * BluetoothUART.cpp
 *
 *  Created on: Apr 2, 2019
 *      Author: Cassidy
 */

#include <BluetoothUART.h>
#include <DebugUART.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "UART/UART.h"
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"




/**
 * Function for sending a command to the bluetooth module.
 * Need to cast char* to uint8_t* for some buffers.
 * NOTE: right now this should JUST be printing CMD and END
 *          4/5/19 -- doesn't print anything.....NO IDEA WHY!
 */
void bt_uart_cmd(char* cmd, unsigned timeout_ms)
{

    char rn52_cmd_buf[10]; // for detecting CMD\r\n and END\r\n
    char rn52_reply_buf[10];

    // Pull GPIO9 of the bluetooth module low
    // On MSP, set P3.4/PM_UCB2STE low
    P3->SEL0 &= ~BIT4;  // Clear P3.4
    P3->SEL1 &= ~BIT4;  // SEL1 and SEL0 combined for 00b, for GPIO
    P3->DIR |= BIT4;    // Configure the port as output (Pg 696 MSP432 user guide)
    P3->OUT &= ~BIT4;   // Drive the output of this pin low (Pg 696 MSP432 user guide)

    // Monitor the UART_RX line for "CMD\r\n"
    // On MSP, UART_RX line is on P3.2/UCA2RXD
    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, timeout_ms);
    dbg_printf(rn52_cmd_buf);


    // When you pull GPIO9 high, Bluetooth should send "END\r\n"
    P3->OUT |= BIT4;   // Drive the output of this pin high
    bt_uart_read((uint8_t*)rn52_cmd_buf, 10, timeout_ms);
    dbg_printf(rn52_cmd_buf);

}

/**
 * Bluetooth UART wrapper for writing an 8-bit integer array.
 */
void bt_uart_write(const uint8_t * buf, unsigned len)
{

    for(int val = 0; val < len; val++)
    {
        put_val_bt(buf[val]);
    }
}


// buf: buffer to read into
// len: length of buffer (exceeding this would be out of bounds for the buffer)
// returns: Number of characters received
unsigned bt_uart_read(uint8_t * buf, unsigned len, unsigned timeout_ms)
{
    unsigned pos = 0;
    while(pos == 0 || (buf[pos - 1] != '\r' && pos < len))
    {

        buf[pos] = get_val_bt(timeout_ms);
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
char get_val_bt(unsigned timeout_ms)
{
    if(uart_a_getc(EUSCI_A2, &rx_val, timeout_ms))
    {
        return rx_val;
    }
    else
    {
        return '\0';
    }
}

void put_val_bt(uint8_t val) {
    uart_a_submit_for_transmit(EUSCI_A2, val);
}




