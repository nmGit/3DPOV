/*
 * BluetoothUART.cpp
 *
 *  Created on: Apr 12, 2019
 *      Author: Cassidy
 */


#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "RadioUART.h"
#include "spi.h"
#include <BluetoothUART.h>
#include <led.h>
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>

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
    P2->SEL0 &= ~BIT1;  // Clear P3.4
    P2->SEL1 &= ~BIT1;  // SEL1 and SEL0 combined for 00b, for GPIO
    P2->DIR |= BIT1;    // Configure the port as output (Pg 696 MSP432 user guide)
    P2->OUT &= ~BIT1;   // Drive the output of this pin low (Pg 696 MSP432 user guide)

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
    P2->OUT |= BIT1;   // Drive the output of this pin high
    bt_uart_read((uint8_t*)rn52_cmd_buf, 6, 100);
    printf(rn52_cmd_buf);
    //dbg_printf(rn52_cmd_buf);

}

/**
 * Function to initialize the raw Bluetooth data structure
 */
void bt_raw_data_init(void) {

    int i, r, c;

    raw_data = (uint32_t**) malloc(FINS * LEDS_PER_FIN * sizeof(uint32_t));
    for(i = 0; i < FINS; i++) {
        raw_data[i] = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));
    }

    for(r = 0; r < FINS; r++) {
        for(c = 0; c < LEDS_PER_FIN; c++) {
            raw_data[r][c] = 0xE2000000;
        }
    }

}

/**
 * Function to free the raw Bluetooth data structure
 */
void bt_raw_data_free(void) {

    int i;

    for(i = 0; i < FINS; i++) {
        free(raw_data[i]);
        raw_data[i] = NULL;
    }

    free(raw_data);
    raw_data = NULL;

}
/*
 * A packet will come in over bluetooth. It will contain a
 * fin number and a sequence number. The sequence number refers
 * to a single position in the 360 deg sweep of the fin.
 *
 */
bt_uart_get_packet(void) {



}

/**
 * Function for receiving LED data over Bluetooth connection.
 * This data is stored in the raw_data data structure.
 */
void bt_uart_get_data(void)
{
    /* CMS
     * LED data is sent in packets of 32 bits
     * but UART transmits in packets of 8 bits
     * So, receiving data 8 bits at a time to build 32-bit data.
     */
    uint32_t* fin_data;     // data structure for a single fin
    uint32_t led_data;      // data structure for a single LED
    uint8_t data_8bit;      // 8-bit data packet

    uint8_t message[3];     // for sending messages over Bluetooth

    // Confirm connection with computer over Bluetooth
    strcpy((char*)message, "CON");
    bt_uart_write(message, 3);


    // Allocate space for fin_data
    //fin_data = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));

    int r, c, b; // loop variables


    // Image data is being sent when "IMG" is received
    bt_uart_read(message, 3, 10000);
    if (strcmp((char*)message, "IMG") == 0) {

        for (r = 0; r < FINS; r++) {
            for (c = 0; c < LEDS_PER_FIN; c++){
                led_data = 0;
                // Get the 32 bit information in 4 chunks of 8 bits
                // Build in order of highest 8 bits to lowest 8 bits (left shift)
                for (b = TX_PER_LED-1; b >= 0; b--) { // NOTE: need to shift by 24 NOT 32 4/16/19
                    if (b == TX_PER_LED-1) {
                        // Append brightness
                        data_8bit = DIM;
                    } else {
                        // Append LED data coming from Bluetooth
                        bt_uart_read(&data_8bit, 1, TIMEOUT_MS);
                    }
                    // During debug, typing the letter "F" corresponds to
                    // hex value 0x46, NOT 0xFF
                    led_data |= (data_8bit << (BITS_PER_TX*b));

                    // Send confirmation that the Radio board has received data
                    strcpy((char*)message, "REC");
                    bt_uart_write(message, 3);
                }
                raw_data[r][c] = led_data;
            }
            //raw_data[r] = fin_data;
        }
    }

    // Free space used by fin_data
    //free(fin_data);
    //fin_data = NULL;
}


/**
 * Function for receiving LED data over Bluetooth connection.
 * This data is stored in the raw_data data structure.
 */
void bt_uart_get_data_test(void)
{
    /* CMS
     * LED data is sent in packets of 32 bits
     * but UART transmits in packets of 8 bits
     * So, receiving data 8 bits at a time to build 32-bit data.
     */
    uint32_t led_data;      // data structure for a single LED
    uint8_t data_8bit;      // 8-bit data packet

    uint8_t message[3];     // for sending messages over Bluetooth

    // Confirm connection with computer over Bluetooth
    strcpy((char*)message, "CON");
    bt_uart_write(message, 3);


    // Allocate space for fin_data
    //fin_data = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));

    int r, c, b; // loop variables


    // Image data is being sent when "IMG" is received
    bt_uart_read(message, 3, 10000);
    if (strcmp((char*)message, "IMG") == 0) {

        for (r = 0; r < FINS; r++) {
            for (c = 0; c < LEDS_PER_FIN; c++){
                led_data = 0;
                // Get the 32 bit information in 4 chunks of 8 bits
                // Build in order of highest 8 bits to lowest 8 bits (left shift)
                for (b = TX_PER_LED-1; b >= 0; b--) { // NOTE: need to shift by 24 NOT 32 4/16/19
                    if (b == TX_PER_LED-1) {
                        // Append brightness
                        data_8bit = DIM;
                    } else {
                        // Append LED data coming from Bluetooth
                        bt_uart_read(&data_8bit, 1, TIMEOUT_MS);
                    }
                    // During debug, typing the letter "F" corresponds to
                    // hex value 0x46, NOT 0xFF
                    led_data |= (data_8bit << (BITS_PER_TX*b));

                    // Send confirmation that the Radio board has received data
                    strcpy((char*)message, "REC");
                    bt_uart_write(message, 3);
                }
                raw_data[r][c] = led_data;
            }
        }
    }

}

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
    if(uart_a_getc(EUSCI_A1, &rx_val, timeout_ms))
    {
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




