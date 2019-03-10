#include <platform_init.h>
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"
// NAM
// UART
char        input;


#define DBG_UART_TX_PIN 2
#define DBG_UART_RX_PIN 3

extern "C" void dbg_UART_init()
{


    // For MCLK
    // Configure UART pins
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART pin as secondary function

    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK
    // Baud Rate calculation
    // N = 48000000/(115200) = 416.66666
    // OS16 = 1
    // UCBRx = N/16 = INT(416.66666/16) = 26 + 0.041667
    // UCBRFx = INT([(N/16) - INT(N/16)] * 16) = INT((8.681 - 8)*16) = INT(10.896) = 10
    // UCBRSx = [(N - INT(N))] = [0.681] = 0xD6

    EUSCI_A0->BRW = 26;                     // 12000000/16/9600
    EUSCI_A0->MCTLW =   (1 << EUSCI_A_MCTLW_BRS_OFS) |
                        (0 << EUSCI_A_MCTLW_BRF_OFS) |
                        EUSCI_A_MCTLW_OS16;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    // Enable global interrupt
    __enable_irq();

    // Enable eUSCIA0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);

    // Enable sleep on exit from ISR
    // SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;


}

void allow_port_mapping()
{
    PMAP->KEYID = 0x02D52;
}

void mux_MCLK_out()
{
    //MCLK on pin 4.3
    P4->DIR |= BIT3;
    P4->SEL1 &= ~BIT3;
    P4->SEL0 |= BIT3;
}
void platform_init()
{
    allow_port_mapping();
    mux_MCLK_out();

    dbg_UART_init();
}
