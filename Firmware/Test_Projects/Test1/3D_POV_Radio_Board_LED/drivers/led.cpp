/******************************************************************************
 * FILE:            led.c                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "./include/led.h"
#include "./include/spi.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "MSP_EXP432P401R.h"


// For holding each individual LED's data
uint8_t global;
uint8_t red_led;
uint8_t blue_led;
uint8_t green_led;

/*
 *  #define RED         0x00FF0000
    #define BLUE        0x0000FF00
    #define GREEN       0x000000FF
 *
 */

//*****************************************************************************
// Flash an LED with a specified color
//*****************************************************************************
void led_flash(uint32_t base, uint8_t brightness, uint32_t color) {

    int c, d; // For the delay for-loop between flashing on and off

    global = brightness | 0xE0;         // Top 3 bits should be 111
    blue_led = (color);         // Find the green LED data in the color
    green_led = (color >> 8);     // Find the blue LED data in the color
    red_led = (color >> 16);     // Find the red LED data in the color
    // Initialize SPI
    spiInit(base);

    // Call SPI transmit function to turn the LED on
    spiTx(base, global, red_led, blue_led, green_led);

    // Reset data to turn off the LED
    global = 0xE0;
    red_led = 0x00;      // Red LED
    blue_led = 0x00;     // Blue LED
    green_led = 0x00;    // Green LED

    // Super arbitrary delay...gotta figure out the math of how quickly to flash this thing!
    for (c = 1; c <= 300; c++)
        for (d = 1; d <= 300; d++)
        {}

    // transmit the data
    spiTx(base, global, red_led, blue_led, green_led);



}

