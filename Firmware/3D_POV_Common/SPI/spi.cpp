/******************************************************************************
 * FILE:            spi.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/20/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "spi.h"

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void spiInit() {

    // Pass to appropriate EUSCI-type initialization method
    if (spi_is_A_type()) {
        spiInit_A_type();
    } else if (spi_is_B_type()) {
        spiInit_B_type();
    } else {
        //printf("Error: base address not correct. Unable to transmit data.");
    }

}

//*****************************************************************************
// Checks if the base address for SPI is type B.
//*****************************************************************************
bool spi_is_B_type(void) {
  if ( base == EUSCI_B0_BASE  ||
        base == EUSCI_B1_BASE ||
        base == EUSCI_B2_BASE ||
        base == EUSCI_B3_BASE
        )
  {
    return true;
  }
  else
  {
    return false;
  }
}


//*****************************************************************************
// Checks if the base address for SPI is type A.
//*****************************************************************************
bool spi_is_A_type(void) {
  if ( base == EUSCI_A0_BASE  ||
        base == EUSCI_A1_BASE ||
        base == EUSCI_A2_BASE ||
        base == EUSCI_A3_BASE
        )
  {
    return true;
  }
  else
  {
    return false;
  }
}

//*****************************************************************************
// General submission method for tx_data.
// Passes to A or B type method depending on SPI base type.
//*****************************************************************************
void submit_for_tx(uint8_t tx_data) {
    if (spi_is_A_type()) {
        submit_for_tx_A(tx_data);
    } else if (spi_is_B_type()) {
        submit_for_tx_B(tx_data);
    }
}

//***************************** A TYPE FUNCTIONS ******************************


//*****************************************************************************
// Transmit the data by putting it into the buffer. A-type base.
//*****************************************************************************
void submit_for_tx_A(uint8_t tx_data) {
    EUSCI_A_SPI_Type* spi_struct = (EUSCI_A_SPI_Type*) base;

    tx_rdy = 0; // Set the hardware transmit boolean to false

    spi_struct -> TXBUF = tx_data; // Shift the data out of the register

    while (!tx_rdy);    // Wait for hardware to be ready to transmit again

}

//*****************************************************************************
// SPI Initialization for A-type base
//*****************************************************************************
void spiInit_A_type() {

    configure_A_pins();     // Configure the pins on the MSP432

    // Cast base_addr to B type
    EUSCI_A_SPI_Type *spi_struct = (EUSCI_A_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_A_CTLW0_SWRST;      // Put in reset
    spi_struct->CTLW0 = EUSCI_A_CTLW0_SWRST |      // Hold in reset
                        EUSCI_A_CTLW0_CKPL |       // Clock polarity
                        EUSCI_A_CTLW0_SYNC |       // Synchronous mode
                        EUSCI_A_CTLW0_MSB |        // MSB first
                        EUSCI_A_CTLW0_MST |        // Master mode
                        EUSCI_A_CTLW0_MODE_1 |     // 4-pin mode
                        EUSCI_A_CTLW0_STEM |       // STE mode select
                        EUSCI_A_CTLW0_SSEL__ACLK;  // ACLK
    spi_struct->BRW = 0x01;                        // Baud Rate 115200

    spi_struct->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;     // Initialize
    spi_struct->IE |=  EUSCI_A_IE_TXIE;// Transmit interrupt enable

    // Enable global interrupt
    __enable_irq();


    // Enable eUSCIAx interrupt in NVIC module -- must define IRQs for all!
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31) |    // eUSCI_B0
                    1 << ((EUSCIA1_IRQn) & 31) |    // eUSCI_B1
                    1 << ((EUSCIA2_IRQn) & 31) |    // eUSCI_B2
                    1 << ((EUSCIA3_IRQn) & 31);     // eUSCI_B3

    // Wake up from LPM on exit from ISR ??????????????????
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();


}

//*****************************************************************************
// Configure the SPI pins on the MSP432 for type A
//*****************************************************************************
void configure_A_pins(void) {

    switch(base) {

        case(EUSCI_A0_BASE):

            P1->SEL0 |= BIT0 | BIT1 | BIT2 | BIT3; // P1.0 is UCA0STE
                                                   // P1.1 is UCA0CLK
                                                   // P1.2 is UCA0SOMI
                                                   // P1.3 is UCA0SIMO

            break;

        case(EUSCI_A1_BASE):

            P2->SEL0 |= BIT0 | BIT1 | BIT2 | BIT3; // P2.0 is UCA1STE
                                                   // P2.1 is UCA1CLK
                                                   // P2.2 is UCA1SOMI
                                                   // P2.3 is UCA1SIMO

            break;

        case(EUSCI_A2_BASE):

            P3->SEL0 |= BIT0 | BIT1 | BIT2 | BIT3; // P3.0 is UCA2STE
                                                   // P3.1 is UCA2CLK
                                                   // P3.2 is UCA2SOMI
                                                   // P3.3 is UCA2SIMO

            break;

        case(EUSCI_A3_BASE):

            P9->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7; // P9.4 is UCA3STE
                                                   // P9.5 is UCA3CLK
                                                   // P9.6 is UCA3SOMI
                                                   // P9.7 is UCA3SIMO

            break;
    }

    // NOTE: Not including a default, not sure if we need one or not?

}



//***************************** B TYPE FUNCTIONS ******************************


//*****************************************************************************
// Transmit the data by putting it into the buffer. B-type base
// tx_data is the 8bit value to transmit.
// When called, the tx_rdy boolean is set to false and tx_data is be placed into
// the SPI struct's TXBUF which will trigger the appropriate IRQ handler.
// This function returns when tx_rdy becomes true again.
//*****************************************************************************
void submit_for_tx_B(uint8_t tx_data) {
    EUSCI_B_SPI_Type* spi_struct = (EUSCI_B_SPI_Type*) base;

    tx_rdy = 0; // Set the hardware transmit boolean to false

    spi_struct -> TXBUF = tx_data; // Shift the data out of the register

    while (!tx_rdy);    // Wait for hardware to be ready to transmit again

}

//*****************************************************************************
// SPI Initialization for B-type base
//*****************************************************************************
void spiInit_B_type() {

    configure_B_pins();     // Configure the pins on the MSP432

    // Cast base_addr to B type
    EUSCI_B_SPI_Type *spi_struct = (EUSCI_B_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_B_CTLW0_SWRST;      // Put in reset
    spi_struct->CTLW0 = EUSCI_B_CTLW0_SWRST |      // Hold in reset
                        EUSCI_B_CTLW0_CKPL |       // Clock polarity
                        EUSCI_B_CTLW0_SYNC |       // Synchronous mode
                        EUSCI_B_CTLW0_MSB |        // MSB first
                        EUSCI_B_CTLW0_MST |        // Master mode
                        EUSCI_B_CTLW0_MODE_1 |     // 4-pin mode
                        EUSCI_B_CTLW0_STEM |       // STE mode select
                        EUSCI_B_CTLW0_SSEL__SMCLK;  // SMCLK
    //    spi_struct->BRW = 0x01;                        // Baud Rate 115200
        spi_struct->BRW = 1;                        // Baud Rate 115200

    spi_struct->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;     // Initialize
    spi_struct->IE |=  EUSCI_B_IE_TXIE;// Transmit interrupt enable

    // Enable global interrupt
    __enable_irq();


    // Enable eUSCIAx interrupt in NVIC module -- must define IRQs for all!
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31) |    // eUSCI_B0
                    1 << ((EUSCIB1_IRQn) & 31) |    // eUSCI_B1
                    1 << ((EUSCIB2_IRQn) & 31) |    // eUSCI_B2
                    1 << ((EUSCIB3_IRQn) & 31);     // eUSCI_B3

    // Wake up from LPM on exit from ISR ??????????????????
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();

}

//*****************************************************************************+
// Configure the SPI pins on the MSP432 for type B
//*****************************************************************************
void configure_B_pins(void) {

    switch(base) {

        case(EUSCI_B0_BASE):

            P1->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7;  // P1.4 is UCB0STE
                                                    // P1.5 is UCB0CLK
                                                    // P1.6 is UCB0SIMO
                                                    // P1.7 is UCB0SOMI
            break;

        case(EUSCI_B1_BASE):

            P6->SEL0 |= BIT2 | BIT3 | BIT4 | BIT5; // P6.2 is UCB1STE
                                                   // P6.3 is UCB1CLK
                                                   // P6.4 is UCB1SIMO
                                                   // P6.5 is UCB1SOMI

            break;

        case(EUSCI_B2_BASE):

            P3->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7; // P3.4 is UCB2STE
                                                   // P3.5 is UCB2CLK
                                                   // P3.6 is UCB2SIMO
                                                   // P3.7 is UCB2SOMI
            break;

        case(EUSCI_B3_BASE):

            P10->SEL0 |= BIT0 | BIT1 | BIT2 | BIT3; // P10.0 is UCB3STE
                                                    // P10.1 is UCB3CLK
                                                    // P10.2 is UCB3SIMO
                                                    // P10.3 is UCB3SOMI
            break;
    }

    // NOTE: Not including a default, not sure if we need one or not?

}





