/******************************************************************************
 * FILE:            spi.h                                                     *
 * AUTHOR:          Cassidy                                                   *
 * DATE CREATED:    2/20/19                                                   *
 *                                                                            *
 *****************************************************************************/

#include "./include/spi.h"
#include <stdint.h>
#include "C:\ti\simplelink_msp432p4_sdk_2_40_00_10\source\ti\devices\msp432p4xx\inc\msp432p401r.h"

uint8_t tx_data;
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
// Transmit method for EUSCI_A_SPI_Type
//*****************************************************************************
void spi_transmit_A_type(void) {

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
                        EUSCI_A_CTLW0_UCSSEL_0;    // UCLK
    spi_struct->BRW = 0x08;                        // ???? Baud rate 115200
    spi_struct->IE |= EUSCI_A_IE_TXIE;             // transmit interrupt enable
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
    // The Data Synchronization Barrier (DSB) instruction ensures that
    // outstanding memory transactions complete before subsequent instructions execute
    __DSB();



    // Enter LPM0 -- processor execution is halted, reducing dynamic power
    while(1) {

        spi_struct->IFG |= EUSCI_A_IFG_TXIFG; // Clear TXIFG flag
        spi_struct->IE |= EUSCI_A__TXIE;      // Enable TX interrupt

        // Enter LPM0
        __sleep();
        __no_operation();                    // For debug

        // No need to check received data since we won't be receiving data

        for(i = 20000; i > 0; i--);     // Delay before next transmission
        tx_data++;                      // Increment transmit data
    }

}


//*****************************************************************************
// Transmit method for EUSCI_B_SPI_Type
//*****************************************************************************
void spi_transmit_B_type(void) {
    // Cast base_addr to B type
    EUSCI_B_SPI_Type *spi_struct = (EUSCI_B_SPI_Type*) base;

    // Configure the struct
    spi_struct->CTLW0 |= EUSCI_B_CTLW0_SWRST;      // put in reset
    spi_struct->CTLW0 = EUSCI_B_CTLW0_SWRST |      // hold in reset
                        EUSCI_B_CTLW0_CKPH |       // data captured THEN changed
                        EUSCI_B_CTLW0_MSB |        // MSB first
                        EUSCI_B_CTLW0_MST |        // Master mode
                        EUSCI_B_CTLW0_UCSSEL_0;    // UCLK
    //spi_struct->BRW = ??                         // something to do with clock...
    spi_struct->IE |=  EUSCI_B_IE_TXIE0;              // transmit interrupt enable
    spi_struct->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;     // Initialize

}


//*****************************************************************************
// General transmit method for SPI
//*****************************************************************************
void spiTx(uint32_t base_in, uint8_t tx_data_in) {

    // Assign base and tx_data
    base = base_in;
    tx_data = tx_data_in;

    P1->OUT &= ~BIT0;
    P1->DIR |= BIT0;                        // Set P1.0 LED

    P1->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7;  // set 4-SPI pin as second function
                                            // P1.4 is UCB0STE
                                            // P1.5 is UCB0CLK
                                            // P1.6 is UCB0SIMO
                                            // P1.7 is UCB0SOMI

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

        // No data being received

    }

}

//*****************************************************************************
// General IRQ B Handler
//*****************************************************************************
void EUSCIBX_IRQHandler(void) {
    EUSCI_B_SPI_Type* spi_struct = (EUSCI_B_SPI_Type*) base;

    // Clear the transmit interrupt flag
       if (spi_struct->IFG & EUSCI_A_IFG_TXIFG) {

           // Transmit characters
           spi_struct->TXBUF = tx_data;

           // Disable transmit interrupts
           spi_struct ->IE &= ~EUSCI_B__TXIE;

       }

}


//*****************************************************************************
// EUSCI type A Handlers
//*****************************************************************************
void EUSCIA0_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

void EUSCIA1_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

void EUSCIA2_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

void EUSCIA3_IRQHandler(void) {
    EUSCIAX_IRQHandler();
}

//*****************************************************************************
// EUSCI type B Handlers
//*****************************************************************************
void EUSCIB0_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

void EUSCIB1_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

void EUSCIB2_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}

void EUSCIB3_IRQHandler(void) {
    EUSCIBX_IRQHandler();
}
