/******************************************************************************
 * FILE:            spi.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/19/19                                                   *
 *                                                                            *
 *****************************************************************************/


#ifndef __ECE453_POV_SPI_H__
#define __ECE453_POV_SPI_H__
#include <stdint.h>


uint32_t base;

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
// LED Count Constants
//*****************************************************************************
#define LEDS_PER_FIN        16     // TESTING -- ultimate goal is 16 LEDs/fin
#define FINS                1     // TESTING -- ultimate goal is 12 fins
#define FRAME_BORDER        4
#define START_FRAME         0x00  // Transmit 4 times for 32 bits of 0
#define END_FRAME           0xFF  // Transmit 4 times for 32 bits of 1

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

//*****************************************************************************
// General IRQ A and B Handlers -- Called by a specific A or B handler
// tx_rdy is set to true and the appropriate interrupt flag is cleared.
//*****************************************************************************
void EUSCIAX_IRQHandler(void);
void EUSCIBX_IRQHandler(void);


#endif
