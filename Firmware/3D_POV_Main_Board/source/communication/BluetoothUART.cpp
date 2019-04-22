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
#include <stdlib.h>
#include "UART/UART.h"
#include "SPI/spi.h"
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"



/**
 * Enter command mode
 */
/*
void bt_enter_cmd_mode(void) {

    char rn52_cmd_buf[6]; // for detecting CMD\r\n

    // Pull GPIO9 of the bluetooth module low
    // On MSP, set P3.4/PM_UCB2STE low
    P3->SEL0 &= ~BIT4;  // Clear P3.4
    P3->SEL1 &= ~BIT4;  // SEL1 and SEL0 combined for 00b, for GPIO
    P3->DIR |= BIT4;    // Configure the port as output (Pg 696 MSP432 user guide)
    P3->OUT &= ~BIT4;   // Drive the output of this pin low (Pg 696 MSP432 user guide)

    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, 1000);
    printf(rn52_cmd_buf);
}

/**
 * Exit command mode
 */
/*
void bt_exit_cmd_mode(void) {

    char rn52_cmd_buf[6]; // for detecting CMD\r\n

    // Pull GPIO9 of the bluetooth module high
    P3->OUT != BIT4;   // Drive the output of this pin low (Pg 696 MSP432 user guide)

    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, 1000);
    printf(rn52_cmd_buf);
}
*/

/**
 * Function for sending a command to the bluetooth module.
 * Need to cast char* to uint8_t* for some buffers.
 *
 * Problems as of 4/9/19: if no command is sent over bt_uart_write, can
 *      make it enter command mode "CMD" and exit command mode "END". But
 *      when I try to make it send commands it suddently doesn't exit
 *      command mode anymore, no more "END" gets displayed??? Also when I send
 *      commands it prints an exclamation point and I don't know what that means :(
 */
void bt_uart_cmd(void)
{

    char rn52_cmd_buf[6]; // for detecting CMD\r\n and END\r\n
    char* rn52_reply_buf = (char*)malloc(256*sizeof(char));

    // Set up cmd buffer
    char *cmd;
    cmd = (char*)malloc(10 * sizeof(char));

    // Pull GPIO9 of the bluetooth module low
    // On MSP, set P3.4/PM_UCB2STE low
    P3->SEL0 &= ~BIT4;  // Clear P3.4
    P3->SEL1 &= ~BIT4;  // SEL1 and SEL0 combined for 00b, for GPIO
    P3->DIR |= BIT4;    // Configure the port as output (Pg 696 MSP432 user guide)
    P3->OUT &= ~BIT4;   // Drive the output of this pin low (Pg 696 MSP432 user guide)

    // Monitor the UART_RX line for "CMD\r\n"
    // On MSP, UART_RX line is on P3.2/UCA2RXD
    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, 1000);
    printf(rn52_cmd_buf);
    //dbg_printf(rn52_cmd_buf);

    /* CMS
     * Commented out this function just prints "CMD" and "END"
     * But when this stuff is here it gets all weird!!! :(
     */
    // Get a command from the command console
    printf("Enter command: ");
    fgets(cmd, 10, stdin);
    bt_uart_write((uint8_t*)cmd, 100);
    bt_uart_read((uint8_t*)rn52_reply_buf,1000);
    printf(rn52_reply_buf);
    //printf("\n");


    // When you pull GPIO9 high, Bluetooth should send "END\r\n"
    P3->OUT |= BIT4;   // Drive the output of this pin high
    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, 100);
    printf(rn52_cmd_buf);
    //dbg_printf(rn52_cmd_buf);

}

/**
 * Function for sending LED data over Bluetooth connection
 */
void bt_uart_send_data(uint32_t ** data)
{
    /* CMS
     * LED data is sent in packets of 32 bits
     * but UART transmits in packets of 8 bits
     */

    int r, c, b;
    uint32_t* fin_data;
    uint32_t led_data;
    uint8_t data_8bit;


    for (r = 0; r < FINS; r++) {
        fin_data = data[r];
        for (c = 0; c < LEDS_PER_FIN; c++){
            led_data = fin_data[c];

            // Send the 32 bit information in 4 chunks of 8 bits
            for (b = 3; b >= 0; b--) {
                // Send in order of highest 8 bits to lowest 8 bits
                data_8bit = (char)(led_data >> (8*b));
                bt_uart_write(&data_8bit, 1);

                // Confirm that the Radio board has received data
                //char rec_msg[4];
                //do {
                //    //bt_uart_read((uint8_t*)rec_msg, 4, 100);
                //} while (strcmp(rec_msg, "REC") != 0);
            }

        }
    }


}
/**
 * Bluetooth UART wrapper for writing an 8-bit integer array.
 */
void bt_uart_write(const uint8_t * buf, unsigned len)
{
    // GPIO9 must be held high on RN52 to send data. This connects to P3.4 on MSP
    P3->SEL0 &= ~BIT4;  // Clear P3.4
    P3->SEL1 &= ~BIT4;  // SEL1 and SEL0 combined for 00b, for GPIO
    P3->DIR |= BIT4;    // Configure the port as output (Pg 696 MSP432 user guide)
    P3->OUT |= BIT4;   // Drive the output of this pin high (Pg 696 MSP432 user guide)

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




