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

// Constants
const uint8_t START_FRAME = 0x00; // Repeat 4 times for 32 bits of 0
const uint8_t END_FRAME = 0xFF;   // Repeat 4 times for 32 bits of 1

// For holding SPI transmit data
uint8_t global_data; // 111 + 5bit global
uint8_t red_data; // Red LED
uint8_t blue_data; // Blue LED
uint8_t green_data; // Green LED

uint8_t c;          // For counting transmissions

uint32_t base;      // Base address of registers using SPI
uint8_t tx_data;    // Used to store the data to transmit in that cycle
uint8_t RXData = 0; // Receive data, unused for our project

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


//*****************************************************************************
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
// Transmit method for EUSCI_A_SPI_Type
//*****************************************************************************
void spi_transmit_A_type(void) {

    volatile uint32_t i;    // For the delay for-loop

    // Cast base_addr to A type
    EUSCI_A_SPI_Type *spi_struct = (EUSCI_A_SPI_Type*) base;

    while(1) {

        spi_struct->IFG |= EUSCI_A_IFG_TXIFG; // Clear TXIFG flag
        spi_struct->IE |= EUSCI_A__TXIE;      // Enable TX interrupt

        // Enter LPM0
        __sleep();
        __no_operation();                    // For debug

        // Transmit Data
        if (c >= 0 && c <= 3) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            c++;
        } else if (c == 4) {
            // 111 + 5bit global (brightness)
            tx_data = global_data;
            c++;
        } else if (c == 5) {
            // Red LED data
            tx_data = red_data;
            c++;
        } else if (c == 6) {
            // Blue LED data;
            tx_data = blue_data;
            c++;
        } else if (c == 7) {
            // Green LED data;
            tx_data = green_data;
            c++;
        } else if (c >= 8 && c <= 10) {
            // 32 bits of 1s define the end frame, send in 8 bit chunks
            tx_data = END_FRAME;
            c++;
        } else {
            // Send the last 8 bits of the end frame separately
            tx_data = END_FRAME;
            c = 0; // Reset count
            for (i = 2000; i > 0; i--); // Delay between each transmission
            return;
        }

    }

}


//*****************************************************************************
// Transmit method for EUSCI_B_SPI_Type
//*****************************************************************************
void spi_transmit_B_type(void) {

    volatile uint32_t i;    // for the delay for-loop

    // Cast base_addr to B type
    EUSCI_B_SPI_Type *spi_struct = (EUSCI_B_SPI_Type*) base;

    while(1) {

        spi_struct->IFG |= EUSCI_B_IFG_TXIFG; // Clear TXIFG flag
        spi_struct->IE |= EUSCI_B__TXIE;      // Enable TX interrupt

        // Enter LPM0
        __sleep();
        __no_operation();                    // For debug

        // Transmit Data
        if (c >= 0 && c <= 3) {
            // 32 bits of 0s define the start frame, send in 8 bit chunks
            tx_data = START_FRAME;
            c++;
        } else if (c == 4) {
            // 111 + 5bit global (brightness)
            tx_data = global_data;
            c++;
        } else if (c == 5) {
            // Red LED data
            tx_data = red_data;
            c++;
        } else if (c == 6) {
            // Blue LED data;
            tx_data = blue_data;
            c++;
        } else if (c == 7) {
            // Green LED data;
            tx_data = green_data;
            c++;
        } else if (c >= 8 && c <= 10) {
            // 32 bits of 1s define the end frame, send in 8 bit chunks
            tx_data = END_FRAME;
            c++;
        } else {
            // Send the last 8 bits of the end frame separately
            tx_data = END_FRAME;
            c = 0; // Reset count
            for (i = 2000; i > 0; i--); // Delay between each transmission
            return;
        }

    }
}

//*****************************************************************************
// SPI Initialization for A-type base
//*****************************************************************************
void spiInit_A_type() {

    configure_A_pins();     // Configure the pins on the MSP432

    // Cast base_addr to A type
    EUSCI_A_SPI_Type *spi_struct = (EUSCI_A_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_A_CTLW0_SWRST;      // Put in reset
    spi_struct->CTLW0 = EUSCI_A_CTLW0_SWRST |      // Hold in reset
                        EUSCI_A_CTLW0_CKPL |       // Clock polarity
                        EUSCI_A_CTLW0_SYNC |       // Synchronous mode
                        EUSCI_A_CTLW0_MSB |        // MSB first
                        EUSCI_A_CTLW0_MST |        // Master mode
                        EUSCI_A_CTLW0_MODE_1 |     // 4-pin mode
                        EUSCI_B_CTLW0_STEM |       // STE mode select
                        EUSCI_A_CTLW0_SSEL__ACLK;  // ACLK
    spi_struct->BRW = 0x01;                        // Baud rate 115200
    spi_struct->IE |= EUSCI_A_IE_TXIE;             // Transmit interrupt enable

    spi_struct->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;     // Initialize

    // Enable global interrupt
    __enable_irq();


    // Enable eUSCIAx interrupt in NVIC module -- must define IRQs for all!
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31) |    // eUSCI_A0
                    1 << ((EUSCIA1_IRQn) & 31) |    // eUSCI_A1
                    1 << ((EUSCIA2_IRQn) & 31) |    // eUSCI_A2
                    1 << ((EUSCIA3_IRQn) & 31);     // eUSCI_A3

    // Wake up from LPM on exit from ISR ??????????????????
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();



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
    spi_struct->IE |=  EUSCI_B_IE_TXIE0;           // Transmit interrupt enable

    spi_struct->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;     // Initialize


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

//*****************************************************************************
// General initialization method for SPI
//*****************************************************************************
void spiInit(uint32_t base_in) {

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
void spiTx(uint32_t base_in, uint8_t global, uint8_t red_led,
                             uint8_t blue_led, uint8_t green_led) {


    // Assign base and LED frames
    base = base_in;
    global_data = global;
    red_data = red_led;
    blue_data = blue_led;
    green_data = green_led;

    // Initialize the transmission count to 0
    c = 0;

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
// General IRQ A Handler
//*****************************************************************************
void EUSCIAX_IRQHandler(void) {
    EUSCI_A_SPI_Type* spi_struct = (EUSCI_A_SPI_Type*) base;

    // Clear the transmit interrupt flag
    if (spi_struct->IFG & EUSCI_A_IFG_TXIFG) {

        // Transmit characters
        spi_struct->TXBUF = tx_data;

        // Disable transmit interrupt
        spi_struct ->IE &= ~EUSCI_A__TXIE;

        // Wait till a character is received
        while (!(spi_struct->IFG & EUSCI_A_IFG_RXIFG));

        // Move data to a temporary buffer
        RXData = spi_struct->RXBUF;

        // Clear the receive interrupt flag
        spi_struct->IFG &= ~EUSCI_A_IFG_RXIFG;

    }

}

//*****************************************************************************
// General IRQ B Handler
//*****************************************************************************
void EUSCIBX_IRQHandler(void) {
    EUSCI_B_SPI_Type* spi_struct = (EUSCI_B_SPI_Type*) base;

    // Clear the transmit interrupt flag
    if (spi_struct->IFG & EUSCI_B_IFG_TXIFG) {

       // Transmit characters
       spi_struct->TXBUF = tx_data;

       // Disable transmit interrupts
       spi_struct ->IE &= ~EUSCI_B__TXIE;

       // Wait till a character is received
       while (!(spi_struct->IFG & EUSCI_B_IFG_RXIFG));

       // Move data to a temporary buffer
       RXData = spi_struct->RXBUF;

       // Clear the receive interrupt flag
       spi_struct->IFG &= ~EUSCI_B_IFG_RXIFG;

    }

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
