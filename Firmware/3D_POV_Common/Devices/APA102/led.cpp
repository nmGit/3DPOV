/******************************************************************************
 * FILE:            led.c                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "led.h"

//*****************************************************************************
// Initialize the image data structure
//*****************************************************************************
void led_init(void) {

    brightness = DIM;
    int fin_idx, pos_idx, led_idx;

    // Allocate space for the image
    image = (position_type**)malloc(sizeof(position_type*) * TOTAL_POS);

    // Allocate space for all positions
    for (pos_idx = 0; pos_idx < TOTAL_POS; pos_idx++) {
        image[pos_idx] = (position_type*)malloc(sizeof(position_type));
        image[pos_idx]->pos_idx = pos_idx;
        image[pos_idx]->all_fins = (fin_type**)malloc(sizeof(fin_type*) * FINS);

        // Allocate space for all fins and all leds
        for(fin_idx = 0; fin_idx < FINS; fin_idx++) {
            image[pos_idx]->all_fins[fin_idx] = (fin_type*)malloc(sizeof(fin_type));
            image[pos_idx]->all_fins[fin_idx]->fin_idx = fin_idx;
            image[pos_idx]->all_fins[fin_idx]->leds = (led_type**)malloc(sizeof(led_type*) * LEDS_PER_FIN);

            // Allocate space for all leds
            for(led_idx = 0; led_idx < LEDS_PER_FIN; led_idx++) {
                image[pos_idx]->all_fins[fin_idx]->leds[led_idx] = (led_type*)malloc(sizeof(led_type));

                // Set brightness to none
                image[pos_idx]->all_fins[fin_idx]->leds[led_idx]->brightness = brightness;

                // Set color to off
                color_set(&(image[pos_idx]->all_fins[fin_idx]->leds[led_idx]->color), OFF);


            }
        }
    }

}

//*****************************************************************************
// Initialize the Bluetooth image buffer
//*****************************************************************************
void led_bt_buf_init() {

    int pos_idx, led_idx;

    // Allocate space for the Bluetooth image buffer
    bt_buffer = (img_pos_packet*)malloc(sizeof(img_pos_packet));

}

//*****************************************************************************
// Get a packet of information over Bluetooth.
// If packet is image information (IMG), fill in the bt_buffer
//*****************************************************************************
void led_bt_get_packet() {

    uint8_t msg[32];    // For sending messages over bluetooth

//    // Send connection message to Bluetooth master
//    strcpy((char*)msg, "CON");
//    bt_uart_write(msg, 4);

    // Find out what type of packet Bluetooth master is sending
    printf("Trying to read line\n");
    while(!read_line((char*)msg, 32))
    {
        for(int i = 0; i < 10000; i++) {
            asm("");
        }
    }
    printf("Received Line: %s\n",msg);
    /*
    if (strcmp((char*)msg, "IMG") == 0) {
        led_bt_fill_buffer();
    } else */
    if (strncmp((char*)msg, "*IDN?", 5) == 0) {
        strcpy((char*)msg,"3DRadio");
        bt_uart_write(msg, 8);
    }


}

//*****************************************************************************
// Fill in the Bluetooth buffer.
// Use the Bluetooth buffer to fill in the image structure.
//*****************************************************************************
void led_bt_fill_buffer() {

    uint8_t msg[4];    // For sending messages over bluetooth

    // Map the Bluetooth data to the bt_buffer structure
    bt_uart_read((uint8_t*)bt_buffer, sizeof(img_pos_packet));

    strcpy((char*)msg, "REC:");
    bt_uart_write(msg, 4);
    bt_uart_write((uint8_t*)bt_buffer, sizeof(img_pos_packet));

    strcpy((char*)msg,"\r\n");
    bt_uart_write(msg, 3);

    // Fill in the image data structure with information from Bluetooth
    led_set_pos(bt_buffer->pos_idx,
                bt_buffer->fin_idx,
                bt_buffer->led_colors);

    // Send a finish message to Bluetooth master
    strcpy((char*)msg, "END");
    bt_uart_write(msg, 4);

}

//*****************************************************************************
// Set a single LED with a specified color
// Assumes curr_led is pointing to the specific LED to set
//*****************************************************************************
void led_set(color_type led_color) {

    curr_led->brightness = brightness | 0xE0;     // Top 3 bits should be 111
    curr_led->color = led_color;

}

//*****************************************************************************
// Set the LEDs of a single fin
// Assumes curr_fin is pointing to the specific fin to set
// and that led_colors is an array containing colors for all LEDs on that fin
//*****************************************************************************
void led_set_fin(color_type* led_colors) {

    int led_idx;

    for (led_idx = 0; led_idx < LEDS_PER_FIN; led_idx++) {
        curr_led = curr_fin->leds[led_idx];
        led_set(led_colors[led_idx]);
    }

}

//*****************************************************************************
// Set the LEDs of a specific fin for a single position
//*****************************************************************************
void led_set_pos(uint8_t fin_idx, uint8_t pos_idx, color_type* led_colors) {

    // Point to the fin indicated by fin_idx
    curr_fin = image[pos_idx]->all_fins[fin_idx];

    // Set the fin
    led_set_fin(led_colors);

}

//*****************************************************************************
// Function to use for setting test colors
//*****************************************************************************
void color_set(color_type* test_color, uint32_t color_value) {
    test_color->blue = (color_value);
    test_color->green = (color_value >> 8);
    test_color->red = (color_value >> 16);
}

//*****************************************************************************
// Function to use for testing fins
//*****************************************************************************
void led_set_test(uint32_t color_value) {

    int pos_idx, fin_idx, led_idx;

    // Allocate space for test colors
    color_type* test_colors = (color_type*)malloc(sizeof(color_type) * LEDS_PER_FIN);
    for (led_idx = 0; led_idx < LEDS_PER_FIN; led_idx++) {
        // Set test color
        color_set(&test_colors[led_idx], color_value);
    }


    for (pos_idx = 0; pos_idx < TOTAL_POS; pos_idx++) {
        for (fin_idx = 0; fin_idx < FINS; fin_idx++) {
            led_set_pos(fin_idx, pos_idx, test_colors);
        }
    }
}

//*****************************************************************************
// Data transmit method for turning on LEDs
// Assumes the entire image data structure has been set in memory
//*****************************************************************************
void led_transmit_data(uint8_t pos_idx) {


    // Initialize the SPI transmission counter and total number of transmissions
    trn = 0;
    total_trn = FRAME_BORDER + (TX_PER_LED*LEDS_PER_FIN*FINS) + FRAME_BORDER;

    uint8_t trn_per_led;    // Counts 4 transmissions per LED frame
    uint8_t tx_data;        // LED data to transmit over SPI interface

    int fin_idx, led_idx;

    while(trn < total_trn) {

        // Transmit Data

        if (trn >= 0 && trn < FRAME_BORDER) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            submit_for_tx(tx_data);
            trn++;


        } else if (trn >= FRAME_BORDER && trn < (TX_PER_LED*LEDS_PER_FIN*FINS) + FRAME_BORDER) {
            // Next, send all of the LED frames
            for (fin_idx = 0; fin_idx < FINS; fin_idx++) {
                curr_fin = image[pos_idx]->all_fins[fin_idx];
                for (led_idx = 0; led_idx < LEDS_PER_FIN; led_idx++) {
                    curr_led = curr_fin->leds[led_idx];
                    for (trn_per_led = 0; trn_per_led < TX_PER_LED; trn_per_led++) {

                        if (trn%4 == 0) {
                            tx_data = curr_led->brightness;
                        } else if (trn%4 == 1) {
                            tx_data = curr_led->color.red;
                        } else if (trn%4 == 2) {
                            tx_data = curr_led->color.blue;
                        } else if (trn%4 == 3) {
                            tx_data = curr_led->color.green;
                        }

                        submit_for_tx(tx_data);
                        trn++; // Increment transmission count
                    }
                }
            }


        } else if (trn >= (TX_PER_LED*LEDS_PER_FIN*FINS)+FRAME_BORDER && trn < total_trn) {
            // 32 bits of 1s define the end frame, send the first three 8 bit chunks
            tx_data = END_FRAME;
            submit_for_tx(tx_data);
            trn++;
        }
    }

    // Reset trn counter to 0 after all transmissions have taken place
    trn = 0;
}


//*****************************************************************************
// Free the LEDs data structure
//*****************************************************************************
void led_free_image(void) {

    int fin_idx, pos_idx, led_idx;


    for (pos_idx = 0; pos_idx < TOTAL_POS; pos_idx++) {
        for(fin_idx = 0; fin_idx < FINS; fin_idx++) {
            for(led_idx = 0; led_idx < LEDS_PER_FIN; led_idx++) {

                // Free space for all LEDs
                free(image[pos_idx]->all_fins[fin_idx]->leds[led_idx]);
            }

            // Free space for all fins
            free(image[pos_idx]->all_fins[fin_idx]->leds);
            free(image[pos_idx]->all_fins[fin_idx]);

        }

        // Free space for all positions
        free(image[pos_idx]->all_fins);
        free(image[pos_idx]);
    }

    // Free space for the image
    free(image);

}

//*****************************************************************************
// Free the Bluetooth buffer
//*****************************************************************************
void led_free_bt_buf() {
    free(bt_buffer);
}

