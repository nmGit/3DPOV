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

//*****************************************************************************
// Globals
//*****************************************************************************

uint32_t base;        // SPI base address


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
//void spiTx(void);

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
// Transmit the data by putting it into the buffer.
// tx_data is the 8bit value to transmit.
// When called, the tx_rdy boolean is set to false and tx_data is be placed into
// the SPI struct's TXBUF which will trigger the appropriate IRQ handler.
// This function returns when tx_rdy becomes true again.
//*****************************************************************************
void submit_for_tx(uint8_t tx_data);
void submit_for_tx_A(uint8_t tx_data);
void submit_for_tx_B(uint8_t tx_data);



#endif
