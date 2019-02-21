#include <platform_init.h>
#include "UARTMSP432.h"
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"
// NAM
// UART
char        input;
UART_Handle dbguart;
UART_Params dbguartParams;

#define DBG_UART_TX_PIN 2
#define DBG_UART_RX_PIN 3

extern "C" void dbg_UART_init()
{
    // Map pins to uart
    CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
    CS->CTL0 = CS_CTL0_DCORSEL_3;           // Set DCO to 12MHz (nominal, center of 8-16MHz range)
    CS->CTL1 = CS_CTL1_SELA_2 |             // Select ACLK = REFO
               CS_CTL1_SELS_3 |                // SMCLK = DCO
               CS_CTL1_SELM_3;                 // MCLK = DCO
    CS->KEY = 0;                            // Lock CS module from unintended accesses

    // Configure UART pins
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART pin as secondary function

    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK
    // Baud Rate calculation
    // N = 12000000/(115200) = 138.8888
    // OS16 = 1
    // UCBRx = N/16 = INT(138.8888/16) = 8 + 0.681
    // UCBRFx = INT([(N/16) - INT(N/16)] * 16) = INT((8.681 - 8)*16) = INT(10.896) = 10
    // UCBRSx = [(N - INT(N))] = [0.681] = 0xD6

    EUSCI_A0->BRW = 6;                     // 12000000/16/9600
    EUSCI_A0->MCTLW =   (20 << EUSCI_A_MCTLW_BRS_OFS) |
                        (8 << EUSCI_A_MCTLW_BRF_OFS) |
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
void init_clocks()
{
    /* Halting WDT and disabling master interrupts */
        MAP_WDT_A_holdTimer();
        MAP_Interrupt_disableMaster();

        /* Set the core voltage level to VCORE1 */
        MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

        /* Set 2 flash wait states for Flash bank 0 and 1*/
        MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
        MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

        /* Initializes Clock System */
        FlashCtl_setWaitState( FLASH_BANK0, 2);
        FlashCtl_setWaitState( FLASH_BANK1, 2);
        PCM_setPowerState( PCM_AM_DCDC_VCORE1 );
        CS_setDCOCenteredFrequency( CS_DCO_FREQUENCY_48 );
        CS_setDCOFrequency(48000000);
        CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, 1);
        CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, 1);
        CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, 1);

}
void platform_init()
{
    init_clocks();
    allow_port_mapping();
    dbg_UART_init();
}
