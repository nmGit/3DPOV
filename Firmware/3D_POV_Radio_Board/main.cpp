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

uint8_t global;
uint8_t red_led;
uint8_t blue_led;
uint8_t green_led;

//*****************************************************************************
// Set up some test data
// Testing a single "fin," FINS = 1 and LEDS_PER_FIN = 16 (the 2020 string)
//*****************************************************************************
void test_data(void) {

    // Initialize data
    raw_data[0][0] = (DIM << 24) | MAGENTA;
    raw_data[0][1] = (DIM << 24) | RED;
    raw_data[0][2] = (DIM << 24) | ORANGE;
    raw_data[0][3] = (DIM << 24) | YELLOW;
    raw_data[0][4] = (DIM << 24) | GREEN;
    raw_data[0][5] = (DIM << 24) | CYAN;
    raw_data[0][6] = (DIM << 24) | BLUE;
    raw_data[0][7] = (DIM << 24) | PURPLE;
    raw_data[0][8] = (DIM << 24) | LAVENDER;
    raw_data[0][9] = (DIM << 24) | MAGENTA;
    raw_data[0][10] = (DIM << 24) | RED;
    raw_data[0][11] = (DIM << 24) | ORANGE;
    raw_data[0][12] = (DIM << 24) | YELLOW;
    raw_data[0][13] = (DIM << 24) | GREEN;
    raw_data[0][14] = (DIM << 24) | CYAN;
    raw_data[0][15] = (DIM << 24) | BLUE;

}


//*****************************************************************************
// Main Method
//*****************************************************************************
int main(void) {

    // Set up test data
    // test_data();

    //WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
    //        WDT_A_CTL_HOLD;

    /* platform_init:
     *  - Sets SPI base address
     *  - Creates LED data structure
     *  - Creates raw data structure for Bluetooth communication
     *  - Initializes SPI pins on MSP432
     *  - Initializes Bluetooth UART pins on MSP432
     */
    disable_wdt();
    //Board_init();
    processor_init();
    platform_init();

    //led_set_image(data);
    led_set_all(NONE, OFF);

    //Set LED at row, col
    led_set_all(DIM, BLUE);
    led_set_all(DIM, MAGENTA);
    led_set_all(DIM, RED);
    led_set_all(DIM, YELLOW);
    led_set_all(DIM, GREEN);
    led_set_all(DIM, CYAN);

    //`led_set_all(NONE, OFF);




    int i;
    while(1) {
        //for (i = 0; i < 100000; i++);
        //bt_uart_write((uint8_t *)&msg, 1);
    }

    return 0;

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
