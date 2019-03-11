/******************************************************************************
 * FILE:            led.c                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "./include/led.h"
#include "./include/spi.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "MSP_EXP432P401R.h"


//*****************************************************************************
// Full LED Data Structure
// 12 rows for all 12 fins
// 16 columns for all 16 LEDs on each fin
//*****************************************************************************


//*****************************************************************************
// Initialize all LEDs -- 12 rows by 16 columns for all 192 LEDs
//*****************************************************************************
void led_init(void) {

    int i, j;

    // Allocate memory for the full LED data structure
    LEDS = (data_frame_type***) malloc(FINS * LEDS_PER_FIN * sizeof(data_frame_type**));
    for(i = 0; i < FINS; i++) {
        LEDS[i] = (data_frame_type**) malloc(LEDS_PER_FIN * sizeof(data_frame_type*));
        for(j = 0; j < LEDS_PER_FIN; j++) {
            LEDS[i][j] = (data_frame_type*) malloc(sizeof(data_frame_type));
        }
    }

    // Set all LEDs to 0
    for(i = 0; i < FINS; i++) {
        for (j = 0; j < LEDS_PER_FIN; j++) {
            LEDS[i][j]->brightness = 0xE0;  // Top 3 bits of this part should be 111
            LEDS[i][j]->red = 0x00;
            LEDS[i][j]->blue = 0x00;
            LEDS[i][j]->green = 0x00;
        }
    }

}

//*****************************************************************************
// Free the LEDs data structure
//*****************************************************************************
void led_free(void) {

    // Free in the opposite order allocated
    int i, j;
    for(i = 0; i < FINS; i++) {
        for (j = 0; j < LEDS_PER_FIN; j++) {
            free(LEDS[i][j]);
            LEDS[i][j] = NULL;
        }
        free(LEDS[i]);
        LEDS[i] = NULL;
    }
    free(LEDS);
    LEDS = NULL;
}

//*****************************************************************************
// Set a single LED with a specified color
//*****************************************************************************
void led_set(uint32_t base, uint8_t led_row, uint8_t led_col,
             uint8_t brightness, uint32_t color) {

    LEDS[led_row][led_col]->brightness = brightness | 0xE0; // Top 3 bits should be 111
    LEDS[led_row][led_col]->red = (color);                 // Find the blue LED data in the color
    LEDS[led_row][led_col]->green = (color >> 8);           // Find the green LED data in the color
    LEDS[led_row][led_col]->blue = (color >> 16);            // Find the red LED data in the color

    // Call SPI transmit function to turn the LED on
    spiTx();

}

//*****************************************************************************
// Set the LEDs of a single fin with data transferred over
// from the interface board.
//*****************************************************************************
void led_set_fin(uint8_t fin, uint32_t* data) {

    int i; // loop counter
    for (i = 0; i < 16; i++) {
        LEDS[fin][i]->brightness = data[i] >> 24;   // Brightness is top 8 bits
        LEDS[fin][i]->blue = data[i] >> 16;         // Blue is next 8 bits
        LEDS[fin][i]->green = data[i] >> 8;         // Green is next 8 bits
        LEDS[fin][i]->red = data[i];                // Red is last 8 bits
    }

}

//*****************************************************************************
// Set the LEDs of all fins with data transferred over
// from the interface board.
//*****************************************************************************
void led_set_image(uint32_t** data) {

    // Update the LEDS data structure
    int i; // loop counter
    for (i = 0; i < FINS; i++){
        // Set each fin's data
        led_set_fin(i, data[i]);
    }

    // Turn on the LEDs
    spiTx();

}

//*****************************************************************************
// set all LEDs from 0 to numLEDs with a specified color //JS
//*****************************************************************************
void led_set_all(uint32_t base, uint8_t num_rows, uint8_t num_cols,
             uint8_t brightness, uint32_t color) {
    uint8_t r,c;
    for (r = 0; r < num_rows; r++) {
        for (c = 0; c < num_cols; c++) {
            led_set(base, r, c, brightness, color);
        }
    }


}




