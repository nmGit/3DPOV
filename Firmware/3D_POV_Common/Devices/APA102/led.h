/******************************************************************************
 * FILE:            led.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/26/19                                                   *
 *                                                                            *
 *****************************************************************************/

#ifndef __ECE453_POV_LED_H__
#define __ECE453_POV_LED_H__
#include <stdint.h>

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
// Single LED Data Structure
//*****************************************************************************
typedef struct {
    uint8_t brightness;     // 111 + 5bit brightness
    uint8_t red;            // 8bit red data
    uint8_t blue;           // 8bit blue data
    uint8_t green;          // 8bit green data
} data_frame_type;

//*****************************************************************************
// Full LED Data Structure
// 12 rows for all 12 fins
// 16 columns for all 16 LEDs on each fin
//*****************************************************************************
data_frame_type*** LEDS;

//*****************************************************************************
// Image data structure
// Contains information for all LEDs for a single position (out of 100)
// in the 360 degree sweep of the image.
//*****************************************************************************


//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// Initialize data structure of LEDs
//*****************************************************************************
void led_init(void);

//*****************************************************************************
// Free the LEDs data structure
//*****************************************************************************
void led_free(void);

//*****************************************************************************
// Set an LED with a specified color and brightness
//*****************************************************************************
void led_set(uint8_t led_row, uint8_t led_col,
             uint8_t brightness, uint32_t led_color);

//*****************************************************************************
// Set the LEDs of a single fin with data transferred over
// from the interface board.
//*****************************************************************************
void led_set_fin(uint8_t fin, uint32_t* data);

//*****************************************************************************
// Set the LEDs of all fins with data transferred over
// from the interface board.
//*****************************************************************************
void led_set_image(uint32_t** data);

//*****************************************************************************
// set all LEDs from 0 to numLEDs with a specified color
//*****************************************************************************
void led_set_all(uint8_t brightness, uint32_t led_color);

//*****************************************************************************
// transmit function to turn on LEDs
//*****************************************************************************
void led_transmit_data(void);
void led_transmit_B_type(void);
void led_transmit_A_type(void);



#endif
