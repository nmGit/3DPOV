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

uint8_t start_frame = 0x00; // repeat 4 times for 32 bits of 0
uint8_t end_frame = 0xFF;   // repeat 4 times for 32 bits of 1

uint8_t led_data_1; // 111 + 5bit global
uint8_t led_data_2; // Red LED
uint8_t led_data_3; // Blue LED
uint8_t led_data_4; // Green LED

uint8_t c;  // for counting transmissions

uint8_t tx_data;
uint8_t RXData = 0;
uint32_t base;

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
// Configure the SPI pins for type A
//*****************************************************************************
void configure_A_pins(void) {

    switch(base) {

        case(EUSCI_B0_BASE):

            break;

        // NOTE: Cases for A0, A1, A2, A3 still need to be configured

    }
}


//*****************************************************************************
// Configure the SPI pins for type B
//*****************************************************************************
void configure_B_pins(void) {

    switch(base) {

        case(EUSCI_B0_BASE):

            P1->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7;  // set 4-SPI pin as second function
                                                    // P1.4 is UCB0STE
                                                    // P1.5 is UCB0CLK
                                                    // P1.6 is UCB0SIMO
                                                    // P1.7 is UCB0SOMI
            break;

        // NOTE: Cases for B1, B2, B3 still need to be configured

    }
}

//*****************************************************************************
// Transmit method for EUSCI_A_SPI_Type
//*****************************************************************************
void spi_transmit_A_type(void) {

    configure_A_pins();

    volatile uint32_t i;    // for the delay for-loop

    // Cast base_addr to A type
    EUSCI_A_SPI_Type *spi_struct = (EUSCI_A_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_A_CTLW0_SWRST;      // put in reset
    spi_struct->CTLW0 = EUSCI_A_CTLW0_SWRST |      // hold in reset
                        EUSCI_A_CTLW0_CKPH |       // data captured THEN changed
                        EUSCI_A_CTLW0_MSB |        // MSB first
                        EUSCI_A_CTLW0_MST |        // Master mode
                        EUSCI_A_CTLW0_MODE_1 |     // 4-pin mode
                        EUSCI_A_CTLW0_UCSSEL_1;    // ACLK
    spi_struct->BRW = 0x01;                        // ???? Baud rate 115200
    spi_struct->IE |= EUSCI_A_IE_TXIE;             // transmit interrupt enable
    spi_struct->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;     // Initialize

    // Enable global interrupt
    //__enable_irq();


    // Enable eUSCIAx interrupt in NVIC module -- must define IRQs for all!
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31) |    // eUSCI_A0
                    1 << ((EUSCIA1_IRQn) & 31) |    // eUSCI_A1
                    1 << ((EUSCIA2_IRQn) & 31) |    // eUSCI_A2
                    1 << ((EUSCIA3_IRQn) & 31);     // eUSCI_A3

    // Wake up from LPM on exit from ISR ??????????????????
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    // The Data Synchronization Barrier (DSB) instruction ensures that
    // outstanding memory transactions complete before subsequent instructions execute
    //__DSB();



    // Enter LPM0 -- processor execution is halted, reducing dynamic power
    while(1) {

        spi_struct->IFG |= EUSCI_A_IFG_TXIFG; // Clear TXIFG flag
        spi_struct->IE |= EUSCI_A__TXIE;      // Enable TX interrupt

        // Enter LPM0
        //__sleep();
        // __no_operation();                    // For debug

        // No need to check received data since we won't be receiving data

    }

}


//*****************************************************************************
// Transmit method for EUSCI_B_SPI_Type
//*****************************************************************************
void spi_transmit_B_type(void) {

    configure_B_pins();

    volatile uint32_t i;    // for the delay for-loop

    // Cast base_addr to B type
    EUSCI_B_SPI_Type *spi_struct = (EUSCI_B_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_B_CTLW0_SWRST;      // put in reset
    spi_struct->CTLW0 = EUSCI_B_CTLW0_SWRST |      // hold in reset
                        EUSCI_B_CTLW0_CKPL |       // Clock polarity
                        EUSCI_B_CTLW0_SYNC |       // Synchronous mode
                        EUSCI_B_CTLW0_MSB |        // MSB first
                        EUSCI_B_CTLW0_MST |        // Master mode
                        EUSCI_B_CTLW0_MODE_1 |     // 4-pin mode
                        EUSCI_B_CTLW0_STEM |       // STE mode select
                        EUSCI_B_CTLW0_SSEL__ACLK;  // ACLK
    spi_struct->BRW = 0x01;                         // something to do with clock...
    spi_struct->IE |=  EUSCI_B_IE_TXIE0;              // transmit interrupt enable
    spi_struct->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;     // Initialize
    // Enable global interrupt
    __enable_irq();


    // Enable eUSCIAx interrupt in NVIC module -- must define IRQs for all!
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31) |    // eUSCI_A0
                    1 << ((EUSCIB1_IRQn) & 31) |    // eUSCI_A1
                    1 << ((EUSCIB2_IRQn) & 31) |    // eUSCI_A2
                    1 << ((EUSCIB3_IRQn) & 31);     // eUSCI_A3

    // Wake up from LPM on exit from ISR ??????????????????
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    // The Data Synchronization Barrier (DSB) instruction ensures that
    // outstanding memory transactions complete before subsequent instructions execute
    __DSB();


    // Enter LPM0 -- processor execution is halted, reducing dynamic power
    while(1) {

        spi_struct->IFG |= EUSCI_B_IFG_TXIFG; // Clear TXIFG flag
        spi_struct->IE |= EUSCI_B__TXIE;      // Enable TX interrupt

        // Enter LPM0
        __sleep();
        __no_operation();                    // For debug

        // No need to check received data since we won't be receiving data
        if (c >= 0 && c <= 3) {
            tx_data = start_frame;
            c++;
        } else if (c == 4) {
            tx_data = led_data_1;
            c++;
        } else if (c == 5) {
            tx_data = led_data_2;
            c++;
        } else if (c == 6) {
            tx_data = led_data_3;
            c++;
        } else if (c == 7) {
            tx_data = led_data_4;
            c++;
        } else if (c >= 8 && c <= 10) {
            tx_data = end_frame;
            c++;
        } else {
            tx_data = end_frame;
            c = 0; // Reset count
            for (i = 2000; i > 0; i--); // Delay between each transmission
        }

    }
}


//*****************************************************************************
// General transmit method for SPI
//*****************************************************************************
void spiTx(uint32_t base_in, uint8_t tx_data_1, uint8_t tx_data_2, uint8_t tx_data_3, uint8_t tx_data_4) {


    // Assign base and LED frames
    base = base_in;
    led_data_1 = tx_data_1;
    led_data_2 = tx_data_2;
    led_data_3 = tx_data_3;
    led_data_4 = tx_data_4;

    // Initialize the transmission count to 0
    c = 0;

    P1->OUT &= ~BIT0;
    P1->DIR |= BIT0;                        // Set P1.0 LED

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
