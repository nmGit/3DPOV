/******************************************************************************
 * FILE:            led.c                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "led.h"
#include "Image.h"

//*****************************************************************************
// Initialize the image data structure
//*****************************************************************************
void led_init(uint8_t bright_val) {

    brightness = bright_val;
//    bt_buffer->pos_idx = 101;

}

//*****************************************************************************
// Get a packet of information over Bluetooth.
// If packet is image information (IMG), fill in the bt_buffer
//*****************************************************************************
uint8_t msg[256];
uint8_t rxmsg[256];
unsigned msg_size;
void led_bt_get_packet() {

    if(read_line((char*)bt_buffer, sizeof(img_pos_packet)))
    {
        if (strncmp((char*)bt_buffer, "IMG", 3) == 0) {
            msg_size = sprintf((char*)rxmsg, "Packet Number: %d\n", bt_buffer->pos_idx);
            bt_uart_write(rxmsg, msg_size);
            led_bt_fill_buffer();
            msg_size = 5;
            rxmsg[0] = 'A';
            rxmsg[1] = 'C';
            rxmsg[2] = 'K';
            rxmsg[3] = ' ';
            rxmsg[4] = (bt_buffer->pos_idx);
            //msg_size = sprintf((char*)rxmsg, "ACK\0%d\n", bt_buffer->pos_idx);
            bt_uart_write(rxmsg, msg_size);
        } else if (strncmp((char*)bt_buffer,"PCK",3) == 0) {
            msg_size = 5;
            rxmsg[0] = 'A';
            rxmsg[1] = 'C';
            rxmsg[2] = 'K';
            rxmsg[3] = ' ';
            rxmsg[4] = (bt_buffer->pos_idx);
            //msg_size = sprintf((char*)rxmsg, "PCK\0%d", bt_buffer->pos_idx);
            bt_uart_write(rxmsg, msg_size);
        } else if (strncmp((char*)bt_buffer,"*IDN?",5) == 0) {
            msg_size = sprintf((char*)rxmsg,"3DRadio");
            bt_uart_write(rxmsg, msg_size);
        }
    }

//    printf("Received line: %s", (char*)bt_buffer);
//    if (strncmp((char*)bt_buffer, "IMG", 3) == 0) {
//        msg_size = sprintf((char*)rxmsg, "Packet Number: %d\n", bt_buffer->pos_idx);
//        bt_uart_write(rxmsg, msg_size);
//        led_bt_fill_buffer();
//        msg_size = sprintf((char*)rxmsg, "END\n");
//        bt_uart_write(rxmsg, msg_size);
//    } else if (strncmp((char*)bt_buffer,"*IDN?",5) == 0) {
//        msg_size = sprintf((char*)rxmsg,"3DRadio");
//        bt_uart_write(rxmsg, msg_size);
//    }

}

//*****************************************************************************
// Use the Bluetooth buffer to fill in the image structure.
//*****************************************************************************
void led_bt_fill_buffer() {

    // Fill in the image data structure with information from Bluetooth
    led_set_pos(bt_buffer->fin_idx,
                bt_buffer->pos_idx,
                bt_buffer->led_colors);


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
// Get a statically stored image from Image.h file
//*****************************************************************************
void led_get_img_str(img_pos_packet* img_array) {

    int pos_idx;

    // Iterate through all positions
    for (pos_idx = 0; pos_idx < TOTAL_POS; pos_idx++) {
        str_buffer = img_array[pos_idx];

        // Fill in the image data structure with information from the array
        led_set_pos(str_buffer.fin_idx,
                    str_buffer.pos_idx,
                    str_buffer.led_colors);
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




