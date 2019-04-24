/******************************************************************************
 * FILE:            led.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/

#ifndef __ECE453_POV_LED_H__
#define __ECE453_POV_LED_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"
#include "BluetoothUART.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "MSP_EXP432P401R.h"

//*****************************************************************************
// Color Constants -- First 8 bits are don't cares, then order is R G B
//*****************************************************************************
#define OFF         0x00000000
#define MAGENTA     0x00FF00FF
#define RED         0x00FF0000
#define ORANGE      0x00FF8000
#define YELLOW      0x00FFFF00
#define GREEN       0x0000FF00
#define CYAN        0x0000FFFF
#define BLUE        0x000000FF
#define PURPLE      0x007F00FF
#define WHITE       0x00FFFFFF
#define LAVENDER    0x00CC99FF

//*****************************************************************************
// Brightness Constants
//*****************************************************************************
#define FULL    0xFF
#define HALF    0xF0
#define DIM     0xE1
#define NONE    0xE0

//*****************************************************************************
// LED Count Constants
//*****************************************************************************
#define LEDS_PER_FIN        16      // TESTING -- ultimate goal is 16 LEDs/fin
#define FINS                3       // TESTING -- ultimate goal is 12 fins
#define TOTAL_POS           1       // TESTING -- ultimately 100 positions per 360 deg sweep
#define TX_PER_LED          4       // 4 SPI transmissions per LED
#define FRAME_BORDER        4       // Each frame byte is sent 4 times for 32 bits
#define START_FRAME         0x00    // Transmit 4 times for 32 bits of 0
#define END_FRAME           0xFF    // Transmit 4 times for 32 bits of 1
#define MSG_LEN             3

//*****************************************************************************
// Globals
//*****************************************************************************
uint8_t trn;          // For counting transmissions
uint8_t total_trn;    // Total number of transmissions


//*****************************************************************************
// Color data structure
//*****************************************************************************
typedef struct {
    uint8_t red;    // 8bit red data
    uint8_t green;  // 8bit green data;
    uint8_t blue;   // 8bit blue data;
} color_type;

//*****************************************************************************
// Single LED Data Structure
//*****************************************************************************
typedef struct {
    uint8_t brightness;          // 111 + 5bit brightness
    color_type color;            // red, blue, green information for entire image
} led_type;

//*****************************************************************************
// Single Fin Data Structure
//*****************************************************************************
typedef struct {
    uint8_t fin_idx;      // Valued at 1 through N total fins
    led_type** leds;      // All LEDs on that fin
} fin_type;

//*****************************************************************************
// Position Data Structure
//*****************************************************************************
typedef struct {
    uint8_t pos_idx;        // Valued at 1 through 100 total positions
    fin_type** all_fins;    // Holds information for all fins at that position
} position_type;

//*****************************************************************************
// Pointers for use within the image data structure
//*****************************************************************************
fin_type* curr_fin;
led_type* curr_led;

//*****************************************************************************
// Global brightness value
//*****************************************************************************
uint8_t brightness;

//*****************************************************************************
// Image position data packet for each of the 100 positions in a 360 deg sweep
//*****************************************************************************
typedef struct {
    uint8_t fin_idx;                      // Valued at 0 through N-1 total fins
    uint8_t pos_idx;                      // 8bit position index, 0 through 99
    color_type led_colors[LEDS_PER_FIN];  // LED color data
    uint8_t checksum;                     // Validity check
} img_pos_packet;

//*****************************************************************************
// Image Data Structures
//*****************************************************************************
position_type** image;                   // Image stored in memory
img_pos_packet* bt_buffer;               // Image buffer from Bluetooth

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// Initialize data structure of LEDs
//*****************************************************************************
void led_init(void);

//*****************************************************************************
// Initialize the Bluetooth image buffer
//*****************************************************************************
void led_bt_image_buf_init(void);

//*****************************************************************************
// Set an LED with a specified color and brightness
// Assumes curr_led is pointing to the specific LED to set
// Assumes curr_fin is pointing to the specific fin to set
// and that led_colors is an array containing colors for all LEDs on that fin
//*****************************************************************************
void led_set(uint32_t led_color);

//*****************************************************************************
// Set the LEDs of a single fin
//*****************************************************************************
void led_set_fin(color_type* led_colors);

//*****************************************************************************
// Set the LEDs of all fins for a single position
//*****************************************************************************
void led_set_pos(uint8_t fin_idx, uint8_t pos_idx, color_type* led_colors);

//*****************************************************************************
// Get a packet of information over bluetooth
//*****************************************************************************
void led_bt_get_packet(void);

//*****************************************************************************
// Fill in the Bluetooth buffer.
// Use the Bluetooth buffer to fill in image structure.
//*****************************************************************************
void led_bt_fill_buffer(void);

//*****************************************************************************
// Function to use for testing fins
//*****************************************************************************
void led_set_test(uint32_t color_value);

//*****************************************************************************
// Function to use for setting test colors
//*****************************************************************************
void color_set(color_type* test_color, uint32_t color_value);

//*****************************************************************************
// Transmit function to turn on LEDs
//*****************************************************************************
void led_transmit_data(uint8_t pos_idx);

//*****************************************************************************
// Free the image data structure
//*****************************************************************************
void led_free_image(void);

//*****************************************************************************
// Free the Bluetooth buffer
//*****************************************************************************
void led_free_bt_buf(void);


#endif
