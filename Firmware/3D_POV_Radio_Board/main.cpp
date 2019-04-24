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
#include "platform_init.h"
#include "BluetoothUART.h"
#include "Board.h"
#include "Proc/processor_init.h"



//*****************************************************************************
// Main Method
//*****************************************************************************
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

    uint32_t i; // for testing with delays

    led_set_test(BLUE);
    led_transmit_data(0);

    while(1){

    }


}

/*
 * Stuff that used to be in main:
 *  // Test led_set_image with some arbitrary data
    // led_set_image(data);
    //led_set_all(base, FINS, LEDS_PER_FIN, NONE, OFF);

    // Set LED at row, col
    //led_set(base, 0, 0, DIM, MAGENTA);
    //led_set(base, 0, 1, FULL, RED);
    //led_set(base, 0, 2, FULL, BLUE);
 */

/* Bluetooth stuff
 *     // Check connection
    char* msg = "hello, world! ";
    bt_uart_write((uint8_t *)msg, 14);


    bt_uart_get_data_test();
    led_set_image(raw_data);


    //platform_free();
 */
