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
#include "spi.h"
#include "led.h"

uint8_t global;
uint8_t red_led;
uint8_t blue_led;
uint8_t green_led;

// Test data
uint32_t** data;

//*****************************************************************************
// Set up some test data
// Testing a single "fin," FINS = 1 and LEDS_PER_FIN = 16 (the 2020 string)
//*****************************************************************************
void test_data(void) {

    int i;

    // Allocate memory for the data structure
    data = (uint32_t**) malloc(FINS * LEDS_PER_FIN * sizeof(uint32_t));
    for(i = 0; i < FINS; i++) {
        data[i] = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));
    }

    int r, c;
    for(r = 0; r < FINS; r++) {
        for(c = 0; c < LEDS_PER_FIN; c++) {
            data[r][c] = 0xE2000000;
        }
    }

    // Initialize data
    data[0][0] = (DIM << 24) | MAGENTA;
    data[0][1] = (DIM << 24) | RED;
    data[0][2] = (DIM << 24) | ORANGE;
    data[0][3] = (DIM << 24) | YELLOW;
    data[0][4] = (DIM << 24) | GREEN;
    data[0][5] = (DIM << 24) | CYAN;
    data[0][6] = (DIM << 24) | BLUE;
    data[0][7] = (DIM << 24) | PURPLE;
    data[0][8] = (DIM << 24) | LAVENDER;
    data[0][9] = (DIM << 24) | MAGENTA;
    data[0][10] = (DIM << 24) | RED;
    data[0][11] = (DIM << 24) | ORANGE;
    data[0][12] = (DIM << 24) | YELLOW;
    data[0][13] = (DIM << 24) | GREEN;
    data[0][14] = (DIM << 24) | CYAN;
    data[0][15] = (DIM << 24) | BLUE;

    //data[1][0] = (DIM << 24) | RED;
}

//*****************************************************************************
// Get data from Bluetooth UART method
// NOTE: Need UART and BluetoothUART in this project!
// CMS: Not a function to keep, just drafting my ideas (4/8/19)
//*****************************************************************************
void get_data(void) {

    // Allocate memory for the data structure
    int i;
    data = (uint32_t**) malloc(FINS * LEDS_PER_FIN * sizeof(uint32_t));
    for(i = 0; i < FINS; i++) {
        data[i] = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));
    }

    // Initialize data structure
    int r, c;
    for(r = 0; r < FINS; r++) {
        for(c = 0; c < LEDS_PER_FIN; c++) {
            data[r][c] = 0xE2000000;
        }
    }

    // Get data from Bluetooth UART
    // Data is sent in groups of 8 bits at a time
    uint32_t* led_whole;     // Entire 32 bit data packet for an individual LED
    uint8_t led_quarter[4];    // One quarter of data for an individual LED
    for (r = 0; r < FINS; r++) {
        for (c = 0; c < LEDS_PER_FIN; c++) {
            for (i = 0; i < 4; i ++) { // 4 bluetooth reads per 1 LED
                //bt_uart_read(&led_quarter[i], 1, 100);
            }
            *led_whole = led_quarter[0] << 24 |
                        led_quarter[1] << 16 |
                        led_quarter[2] << 8  |
                        led_quarter[3] ;
            data[r][c] = *led_whole;
        }
    }

}

//*****************************************************************************
// Main Method
//*****************************************************************************
int main(void) {

    // Set up test data
    // test_data();

    // Set up data received via Bluetooth UART
    get_data();

    base = EUSCI_B2_BASE;

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
            WDT_A_CTL_HOLD;

    // Initialize LEDs
    led_init();

    // Initialize SPI
    spiInit();

    // Test led_set_image with some arbitrary data
    /// led_set_image(data);
    //led_set_all(base, FINS, LEDS_PER_FIN, NONE, OFF);

    // Set LED at row, col
    //led_set(base, 0, 0, DIM, MAGENTA);
    //led_set(base, 0, 1, FULL, RED);
    //led_set(base, 0, 2, FULL, BLUE);

    // JS
/*    uint8_t i;
    for(i = 0; i < 16; i++){
        switch(i){
        case 0:
        case 15:
            led_set_all(base, 1, 16, DIM, PURPLE);
            break;
        case 1:
        case 14:
            led_set_all(base, 1, 16, DIM, RED);
            break;
        case 2:
        case 13:
            led_set_all(base, 1, 16, DIM, ORANGE);
            break;
        case 3:
        case 12:
            led_set_all(base, 1, 16, DIM, YELLOW);
            break;
        case 4:
        case 11:
            led_set_all(base, 1, 16, DIM, GREEN);
            break;
        case 5:
        case 10:
            led_set_all(base, 1, 16, DIM, CYAN);
            break;
        case 6:
        case 9:
            led_set_all(base, 1, 16, DIM, BLUE);
            break;
        case 7:
        case 8:
            led_set_all(base, 1, 16, DIM, OFF);
            break;
        default:
            break;
        }
    }
*/

    // Free LEDs
    //led_free();

    while(1) {

    }

    return 0;

}
