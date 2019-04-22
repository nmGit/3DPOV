/******************************************************************************
 * FILE:            led.c                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "spi.h"
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
            LEDS[i][j]->brightness = 0xE0;
            LEDS[i][j]->red = 0x00;
            LEDS[i][j]->blue = 0x00;
            LEDS[i][j]->green = 0x00;
        }
    }

}

//*****************************************************************************
// set a single LED with a specified color
//*****************************************************************************
void led_set(uint8_t led_row, uint8_t led_col,
             uint8_t brightness, uint32_t led_color) {


    LEDS[led_row][led_col]->brightness = brightness | 0xE0; // Top 3 bits should be 111
    LEDS[led_row][led_col]->blue = (led_color);                 // Find the blue LED data in the color
    LEDS[led_row][led_col]->green = (led_color >> 8);           // Find the green LED data in the color
    LEDS[led_row][led_col]->red = (led_color >> 16);            // Find the red LED data in the color

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
    led_transmit_data();

}

//*****************************************************************************
// set all LEDs from 0 to numLEDs with a specified color //JS
//*****************************************************************************
void led_set_all(uint8_t brightness, uint32_t led_color) {
    uint8_t r,c;
    for (r = 0; r < FINS; r++) {
        for (c = 0; c < LEDS_PER_FIN; c++) {
            led_set(r, c, brightness, led_color);
        }
    }

    // Turn on the LEDs
    led_transmit_data();
}


//*****************************************************************************
// General transmit method for turning on LEDs
//*****************************************************************************
void led_transmit_data() {

    // Initialize the SPI  transmission counter and total number of transmissions
    trn = 0;
    total_trn = FRAME_BORDER + (LEDS_PER_FIN * TX_PER_LED * FINS) + FRAME_BORDER;
                    // 4 for start frame
                    // Plus 4 per LED
                    // Plus 4 for end frame

    // Pass to appropriate EUSCI-type transmit method
    if (spi_is_A_type()) {
        led_transmit_A_type();
    } else if (spi_is_B_type()) {
        led_transmit_B_type();
    } else {
        //printf("Error: base address not correct. Unable to transmit data.");
    }

}


//*****************************************************************************
// Transmit method for EUSCI_B_SPI_Type
// The global variable trn counts the number of transmissions for this
// SPI transaction.
//     - The first four transmissions (trn = 0 to trn = 3)
//       define the start frame, which is 32 bits of 0s.
//     - The next set of transmissions are the LED frames. Information for
//       all LEDs in the data structure will be transmitted in the pattern
//       brightness, red, blue, green.
//     - The last four transmissions define the end frame, which is
//       32 bits of 1s. This is split up into 3 transmissions
//       (for trn >= (LEDS_PER_FIN*FINS)+FRAME_BORDER && trn < total_trn-1)
//       and then the final transmission, which resets the trn count back to 0.
//
//*****************************************************************************
void led_transmit_B_type(void) {

    uint8_t r, c;           // row, column counters for LED data structure
    uint8_t trn_per_led;    // Counts 4 transmissions per LED frame
    uint8_t tx_data;

    while(trn < total_trn) {

        // Transmit Data
        if (trn >= 0 && trn < FRAME_BORDER) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            submit_for_tx_B(tx_data);
            trn++;
        } else if (trn >= FRAME_BORDER && trn < (LEDS_PER_FIN*FINS*TX_PER_LED) + FRAME_BORDER) {
            for (r = 0; r < FINS; r++) {
                for (c = 0; c < LEDS_PER_FIN; c++) {
                    for (trn_per_led = 0; trn_per_led < TX_PER_LED; trn_per_led++) {

                        if (trn%4 == 0) {
                            tx_data = LEDS[r][c]->brightness;
                        } else if (trn%4 == 1) {
                            tx_data = LEDS[r][c]->red;
                        } else if (trn%4 == 2) {
                            tx_data = LEDS[r][c]->blue;
                        } else if (trn%4 == 3) {
                            tx_data = LEDS[r][c]->green;
                        }
                        submit_for_tx_B(tx_data);
                        trn++; // Increment transmission count
                    }
                }
            }
        } else if (trn >= (LEDS_PER_FIN*FINS*TX_PER_LED)+FRAME_BORDER && trn < total_trn) {
            // 32 bits of 1s define the end frame, send the first three 8 bit chunks
            tx_data = END_FRAME;
            submit_for_tx_B(tx_data);
            trn++;
        }
    }

    trn = 0;
}


//*****************************************************************************
// Transmit method for EUSCI_A_SPI_Type
//*****************************************************************************
void led_transmit_A_type(void) {

    uint8_t r, c;           // row, column counters for LED data structure
    uint8_t trn_per_led;    // Counts 4 transmissions per LED frame
    uint8_t tx_data;

    while(trn < total_trn) {

        // Transmit Data
        if (trn >= 0 && trn < FRAME_BORDER) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            submit_for_tx_A(tx_data);
            trn++;
        } else if (trn >= FRAME_BORDER && trn < (LEDS_PER_FIN*FINS*TX_PER_LED) + FRAME_BORDER) {
            for (r = 0; r < FINS; r++) {
                for (c = 0; c < LEDS_PER_FIN; c++) {
                    for (trn_per_led = 0; trn_per_led < 4; trn_per_led++) {

                        if (trn%4 == 0) {
                            tx_data = LEDS[r][c]->brightness;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 1) {
                            tx_data = LEDS[r][c]->red;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 2) {
                            tx_data = LEDS[r][c]->blue;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 3) {
                            tx_data = LEDS[r][c]->green;
                        }

                        submit_for_tx_A(tx_data);
                        trn++; // Increment transmission count
                    }
                }
            }
        } else if (trn >= (LEDS_PER_FIN*FINS*TX_PER_LED)+FRAME_BORDER && trn < total_trn) {
            // 32 bits of 1s define the end frame, send the first three 8 bit chunks
            tx_data = END_FRAME;
            submit_for_tx_A(tx_data);
            trn++;
        }
    }

    trn = 0;

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







