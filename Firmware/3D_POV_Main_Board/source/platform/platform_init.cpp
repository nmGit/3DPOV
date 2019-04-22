#include <platform/platform_init.h>
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "DebugUART.h"
#include "Board.h"
// NAM UART
// JS TIMER/PWM
char        input;


#define DBG_UART_TX_PIN 2
#define DBG_UART_RX_PIN 3

void timerA_init()
{
    // Pin muxing
    P2->DIR  |= BIT4;
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;

//    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_1       // Using SMCLK
//            | TIMER_A_CTL_MC__UP;               // Timer will count up to value in TA0CCR0 and reset (up mode)
//

    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2       // Using SMCLK
            | TIMER_A_CTL_ID_3                  // Divide SMCLK by 8 to get max freq 48MHz/8 = 6 MHz
            | TIMER_A_CTL_MC__UP;               // Timer will count up to value in TA0CCR0 and reset (up mode)

    TIMER_A0->EX0 |= TIMER_A_EX0_TAIDEX_7;      // Divide SMCLK by 8 to get 6MHz/8 = 750 kHz

    // USED to limit timer counter (TA0CCR0)
    TIMER_A0->CCR[0] = PWM_WRAP_VAL;            // Max frequency of 50Hz (0x3B0Dh found by guess and check with Oscilloscope)
                                                //  To set duty cycle change TIMER_A0->CCR[1] in PWM.cpp

    //    TIMER A0 CTL0 does not need to be set since we use CCR0 to limit the timer
}

extern "C" void bt_UART_init() {

    // Configure UART pins
    P3->SEL0 |= BIT2 | BIT3;       // Bit 2 is RX, Bit 3 is TX

    // Configure UART
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;         // Put eUSCI in reset
    EUSCI_A2->CTLW0 = EUSCI_A_CTLW0_SWRST |         // Remain eUSCI in reset
                      EUSCI_A_CTLW0_SSEL__SMCLK;    // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // N = 48000000/(115200) = 416.66666
    // OS16 = 1
    // UCBRx = N/16 = INT(416.66666/16) = 26 + 0.041667
    // UCBRFx = INT([(N/16) - INT(N/16)] * 16) = INT((8.681 - 8)*16) = INT(10.896) = 10
    // UCBRSx = [(N - INT(N))] = [0.681] = 0xD6

    EUSCI_A2->BRW = 26;                     // 12000000/16/9600
    EUSCI_A2->MCTLW =   (1 << EUSCI_A_MCTLW_BRS_OFS) |
                        (0 << EUSCI_A_MCTLW_BRF_OFS) |
                        EUSCI_A_MCTLW_OS16;

    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;     // Clear eUSCI RX interrupt flag
    EUSCI_A2->IE |= EUSCI_A_IE_RXIE;         // Enable USCI_A0 RX interrupt

    // Enable global interrupt
#ifdef NAM
    __enable_irq();
#endif // NAM
    MAP_Interrupt_setPriority(INT_EUSCIA2,0x30);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
#ifdef NAM
    Interrupt_setPriority(INT_EUSCIA2,0x30);
    Interrupt_enableInterrupt( INT_EUSCIA2);
#endif // NAM
#ifdef NAM
    // Enable eUSCIA2 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA2_IRQn) & 31);
#endif // NAM

}

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
#ifdef NAM
    __enable_irq();
#endif // NAM
//    MAP_Interrupt_setPriority(INT_EUSCIA0, 0x30);
 //   MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
   // MAP_UART_enableInterrupt(EUSCI_A0_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_setPriority(INT_EUSCIA0,0x30);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    //MAP_Interrupt_enableSleepOnIsrExit();
    //MAP_Interrupt_enableMaster();
#ifdef NAM
    Interrupt_setPriority(INT_EUSCIA0,0x30);

    Interrupt_enableInterrupt( INT_EUSCIA0);
#endif // NAM
#ifdef NAM
    // Enable eUSCIA0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);
#endif // NAM
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

    bt_UART_init();
    dbg_UART_init();
    timerA_init();
}

void print_init_message()
{
    dbg_printf("-----------------------------\r\n");
    dbg_printf("MCLK at \t%d Hz\r\n", CS_getMCLK());
    dbg_printf("BCLK at \t%d Hz\r\n", CS_getBCLK());
    dbg_printf("HSMCLK at \t%d Hz\r\n", CS_getHSMCLK());
    dbg_printf("DCO at \t\t%d Hz\r\n", CS_getDCOFrequency());
    dbg_printf("-----------------------------\r\n");
}
