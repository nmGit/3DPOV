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
#include "drivers/include/spi.h"
#include "drivers/include/led.h"

uint8_t global;
uint8_t red_led;
uint8_t blue_led;
uint8_t green_led;

//*****************************************************************************
// Main Method
//*****************************************************************************
int main(void) {

    base = EUSCI_B1_BASE;

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
            WDT_A_CTL_HOLD;

    // Initialize LEDs
    led_init();

    // Initialize SPI
    spiInit();

    // Set LED at row, col
    led_set(base, 0, 0, FULL, RED);
    led_set(base, 0, 1, FULL, BLUE);
    //led_set(base, 0, 2, FULL, GREEN);

    while(1) {

    }

    return 0;

}
