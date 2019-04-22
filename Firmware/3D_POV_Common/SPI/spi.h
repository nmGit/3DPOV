/******************************************************************************
 * FILE:            spi.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/19/19                                                   *
 *                                                                            *
 *****************************************************************************/


#ifndef __ECE453_POV_SPI_H__
#define __ECE453_POV_SPI_H__
#include <stdint.h>
#include "irq_handlers.h"
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "MSP_EXP432P401R.h"


uint32_t base;  // SPI base address

//// CMS: color constants & brightness constants copied from led.h for testing
////*****************************************************************************
//// Color Constants -- First 8 bits are don't cares, then order is R G B
////*****************************************************************************
//#define OFF         0x00000000
//#define MAGENTA     0x00FF00FF
//#define RED         0x00FF0000
//#define ORANGE      0x00FF8000
//#define YELLOW      0x00FFFF00
//#define GREEN       0x0000FF00
//#define CYAN        0x0000FFFF
//#define BLUE        0x000000FF
//#define PURPLE      0x007F00FF
//#define WHITE       0x00FFFFFF
//#define LAVENDER    0x00CC99FF
//
////*****************************************************************************
//// Brightness Constants
////*****************************************************************************
//#define FULL    0xFF
//#define HALF    0xF0
//#define DIM     0x1F
//#define NONE    0xE0

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
typedef struct {
    LEDS img[100];
} image_type;


//*****************************************************************************
// LED Count Constants
//*****************************************************************************
#define LEDS_PER_FIN        16      // TESTING -- ultimate goal is 16 LEDs/fin
#define FINS                1       // TESTING -- ultimate goal is 12 fins
#define FRAME_BORDER        4
#define START_FRAME         0x00    // Transmit 4 times for 32 bits of 0
#define END_FRAME           0xFF    // Transmit 4 times for 32 bits of 1
#define TX_PER_LED          4       // 4 SPI transmissions per LED

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void spiInit(void);

//*****************************************************************************
// General transmit method for SPI
//*****************************************************************************
void spiTx(void);

//*****************************************************************************
// Checks if the base address for SPI is type A or type B.
//*****************************************************************************
bool spi_is_A_type(void);
bool spi_is_B_type(void);

//*****************************************************************************
// Initializes SPI for type A or type B.
//*****************************************************************************
void spiInit_A_type(void);
void spiInit_B_type(void);

//*****************************************************************************
// Configure the SPI pins on the MSP432 for type A or type B.
//*****************************************************************************
void configure_A_pins(void);
void configure_B_pins(void);

//*****************************************************************************
// Transmit method for EUSCI_A_SPI_Type or EUSCI_B_SPI_TYPE
//*****************************************************************************
void spi_transmit_A_type(void);
void spi_transmit_B_type(void);

//*****************************************************************************
// Transmit the data by putting it into the buffer.
// tx_data is the 8bit value to transmit.
// When called, the tx_rdy boolean is set to false and tx_data is be placed into
// the SPI struct's TXBUF which will trigger the appropriate IRQ handler.
// This function returns when tx_rdy becomes true again.
//*****************************************************************************
void submit_for_tx_A(uint8_t tx_data);
void submit_for_tx_B(uint8_t tx_data);



#endif
