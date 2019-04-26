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

    led_get_img_str(test_bars);

    int pos = 0;
    shift_out = false;
    while(1){

        // TESTING -- just making an arbitrary delay
        //  for(int i = 0; i < 1000000; i++) {
        //      asm("");
        //  }

        /* NOTE: Instead of some arbitrary delay, going to use SysTick timer.
         * Use the hall effect sensor to find the number of ticks in one full revolution.
         * Divide that number of ticks by 100.
         *
         */
        if(shift_out){
// printf("SHIFT! %d\r\n", pos);
            led_transmit_data(pos);

            // Keep transmitting forever
            pos++;
            pos %= TOTAL_POS;
            shift_out = false;
        }

    }


}

