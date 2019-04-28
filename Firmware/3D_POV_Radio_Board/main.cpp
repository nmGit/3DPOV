/*
 * FILE:         main.cpp
 * AUTHOR:       Cassidy
 * DATE CREATED: 2/19/19
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti/devices/msp432p4xx/driverlib/cs.h"
#include "ti/devices/msp432p4xx/inc/msp.h"
#include "spi.h"
#include "led.h"
#include "hall.h"
#include "platform_init.h"
#include "BluetoothUART.h"
#include "Board.h"
#include "Proc/processor_init.h"
#include "Image.h"



//*****************************************************************************
// Main Method
//*****************************************************************************
//*****************************************************************************
// TELL ME TO SHIFT OR ELSE
//*****************************************************************************
bool shift_out;
extern img_pos_packet test_bars[];

int main(void) {

    /* platform_init:
     *  - Sets SPI base address
     *  - Creates LED data structure
     *  - Creates raw data structure for Bluetooth communication
     *  - Initializes SPI pins on MSP432
     *  - Initializes Bluetooth UART pins on MSP432
     */
    disable_wdt();
    processor_init();
    platform_init();

    // Fill in image data structure using statically stored image
    led_get_img_str(test_bars);

    uint8_t msg[15];
    uint8_t msg_size = sprintf((char*)msg,"hello, world!\n");
    bt_uart_write((uint8_t*)msg,msg_size);

    int pos = 0;
    shift_out = false;
    while(1){

        led_transmit_data(pos);
        pos++;
        pos %= TOTAL_POS;


//      led_bt_get_packet();
//      if(shift_out){
//          led_transmit_data(pos);
//
//          // Keep transmitting forever
//          pos++;
//          pos %= TOTAL_POS;
//          shift_out = false;
//      }

    }


}

