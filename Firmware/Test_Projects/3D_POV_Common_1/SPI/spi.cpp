/******************************************************************************
 * FILE:            spi.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/20/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "./include/spi.h"
#include <stdint.h>
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "MSP_EXP432P401R.h"

//*****************************************************************************
// Globals
//*****************************************************************************
volatile bool tx_rdy; // For alerting when the hardware is ready
                      // to transmit more data

uint8_t trn;          // For counting transmissions
uint8_t total_trn;    // Total number of transmissions

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void spiInit() {

    //base = base_in; // base is now global

    P1->OUT &= ~BIT0;
    P1->DIR |= BIT0;                        // Set P1.0 LED

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
// General transmit method for SPI
//*****************************************************************************
void spiTx() {

    // Initialize the transmission counter and total number of transmissions
    trn = 0;
    total_trn = 8 + (LEDS_PER_FIN * 4 * FINS); // 4 for start frame
                                               // Plus 4 per LED
                                               // Plus 4 for end frame

    // Pass to appropriate EUSCI-type transmit method
    if (spi_is_A_type()) {
        spi_transmit_A_type();
    } else if (spi_is_B_type()) {
        spi_transmit_B_type();
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

//***************************** A TYPE FUNCTIONS ******************************

//*****************************************************************************
// Transmit method for EUSCI_A_SPI_Type
//*****************************************************************************
void spi_transmit_A_type(void) {

    uint8_t r, c;           // row, column counters for LED data structure
    uint8_t trn_per_led;    // Counts 4 transmissions per LED frame
    uint8_t tx_data;

    while(trn < total_trn) {

        // Transmit Data
        if (trn >= 0 && trn <= 3) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            submit_for_tx_A(tx_data);
            trn++;
        } else if (trn > 3 && trn < (LEDS_PER_FIN*FINS) + 4) {
            for (r = 0; r < FINS; r++) {
                for (c = 0; c < LEDS_PER_FIN; c++) {
                    for (trn_per_led = 0; trn_per_led < 4; trn_per_led++) {

                        if (trn%4 == 0) {
                            tx_data = LEDS[r][c]->brightness;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 1) {
                            tx_data = LEDS[r][c]->blue;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 2) {
                            tx_data = LEDS[r][c]->green;
                            submit_for_tx_A(tx_data);
                        } else if (trn%4 == 3) {
                            tx_data = LEDS[r][c]->red;
                            submit_for_tx_A(tx_data);
                        }

                        trn++; // Increment transmission count
                    }
                }
            }
        } else if (trn >= (LEDS_PER_FIN*FINS)+FRAME_BORDER && trn < total_trn) {
            // 32 bits of 1s define the end frame, send the first three 8 bit chunks
            tx_data = END_FRAME;
            submit_for_tx_A(tx_data);
            trn++;
        }
    }

    trn = 0;

}

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
void spi_transmit_B_type(void) {

    uint8_t r, c;           // row, column counters for LED data structure
    uint8_t trn_per_led;    // Counts 4 transmissions per LED frame
    uint8_t tx_data;

    while(trn < total_trn) {

        // Transmit Data
        if (trn >= 0 && trn <= 3) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            submit_for_tx_B(tx_data);
            trn++;
        } else if (trn > 3 && trn < (LEDS_PER_FIN*FINS) + 4) {
            for (r = 0; r < FINS; r++) {
                for (c = 0; c < LEDS_PER_FIN; c++) {
                    for (trn_per_led = 0; trn_per_led < 4; trn_per_led++) {

                        if (trn%4 == 0) {
                            tx_data = LEDS[r][c]->brightness;
                            submit_for_tx_B(tx_data);
                        } else if (trn%4 == 1) {
                            tx_data = LEDS[r][c]->red;
                            submit_for_tx_B(tx_data);
                        } else if (trn%4 == 2) {
                            tx_data = LEDS[r][c]->blue;
                            submit_for_tx_B(tx_data);
                        } else if (trn%4 == 3) {
                            tx_data = LEDS[r][c]->green;
                            submit_for_tx_B(tx_data);
                        }

                        trn++; // Increment transmission count
                    }
                }
            }
        } else if (trn >= (LEDS_PER_FIN*FINS)+FRAME_BORDER && trn < total_trn) {
            // 32 bits of 1s define the end frame, send the first three 8 bit chunks
            tx_data = END_FRAME;
            submit_for_tx_B(tx_data);
            trn++;
        }
    }

    trn = 0;
}


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
                        EUSCI_B_CTLW0_SSEL__ACLK;  // ACLK
    spi_struct->BRW = 0x01;                        // Baud Rate 115200

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


//*****************************************************************************
// General IRQ A Handler
//*****************************************************************************
void EUSCIAX_IRQHandler(void) {
    EUSCI_A_SPI_Type* spi_struct = (EUSCI_A_SPI_Type*) base;

    // Set trx_rdy to true
    tx_rdy = 1;

    // Clear the transmit interrupt flag
    spi_struct->IFG &= ~EUSCI_B_IFG_TXIFG0;

}

//*****************************************************************************
// General IRQ B Handler
//*****************************************************************************
void EUSCIBX_IRQHandler(void) {
    EUSCI_B_SPI_Type* spi_struct = (EUSCI_B_SPI_Type*) base;

    // Set trx_rdy to true
    tx_rdy = 1;

    // Clear the transmit interrupt flag
    spi_struct->IFG &= ~EUSCI_B_IFG_TXIFG0;

}


//*****************************************************************************
// EUSCI type A Handlers
//*****************************************************************************
extern "C" void EUSCIA0_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

extern "C" void EUSCIA1_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

extern "C" void EUSCIA2_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

extern "C" void EUSCIA3_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

//*****************************************************************************
// EUSCI type B Handlers
//*****************************************************************************
extern "C" void EUSCIB0_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB1_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB2_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

extern "C" void EUSCIB3_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}
