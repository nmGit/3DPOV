#include "platform_init.h"
#include "spi.h"
#include "led.h"
#include "BluetoothUART.h"
#include "MSP_EXP432P401R.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>

char        input;


#define DBG_UART_TX_PIN 2
#define DBG_UART_RX_PIN 3


extern "C" void bt_UART_init() {

    // Configure UART pins
    P2->SEL0 |= BIT2 | BIT3;       // Bit 2 is RX, Bit 3 is TX

    // Configure UART
    EUSCI_A1->CTLW0 |= EUSCI_A_CTLW0_SWRST;         // Put eUSCI in reset
    EUSCI_A1->CTLW0 = EUSCI_A_CTLW0_SWRST |         // Remain eUSCI in reset
                      EUSCI_A_CTLW0_SSEL__SMCLK;    // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // N = 3000000/(115200) = 26.041667
    // OS16 = 1
    // UCBRx = N/16 = INT(26.041667/16) = 1 + 0.6276041667
    // UCBRFx = INT([(N/16) - INT(N/16)] * 16) = INT((1.6276041667 - 1)*16) = INT(10.041667) = 10
    // UCBRSx = [(N - INT(N))] = [0.6276041667] = 0xB5

    EUSCI_A1->BRW = 1;                     // 12000000/16/9600
    EUSCI_A1->MCTLW =   (181 << EUSCI_A_MCTLW_BRS_OFS) |
                        (10 << EUSCI_A_MCTLW_BRF_OFS) |
                        EUSCI_A_MCTLW_OS16;

    EUSCI_A1->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A1->IFG &= ~EUSCI_A_IFG_RXIFG;     // Clear eUSCI RX interrupt flag
    EUSCI_A1->IE |= EUSCI_A_IE_RXIE /*| EUSCI_A_IE_TXCPTIE*/ | EUSCI_A_IE_TXIE;         // Enable USCI_A0 RX interrupt

    // Enable global interrupt
#ifdef NAM
    __enable_irq();
#endif // NAM
    MAP_Interrupt_setPriority(INT_EUSCIA1,0x30);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA1);
#ifdef NAM
    Interrupt_setPriority(INT_EUSCIA1,0x30);
    Interrupt_enableInterrupt( INT_EUSCIA1);
#endif // NAM
#ifdef NAM
    // Enable eUSCIA2 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA1_IRQn) & 31);
#endif // NAM

}

void allow_port_mapping()
{
    PMAP->KEYID = 0x02D52;
}
void print_init_message()
{
    printf("-----------------------------\r\n");
    printf("MCLK at \t%d Hz\r\n", CS_getMCLK());
    printf("BCLK at \t%d Hz\r\n", CS_getBCLK());
    printf("HSMCLK at \t%d Hz\r\n", CS_getHSMCLK());
    printf("DCO at \t\t%d Hz\r\n", CS_getDCOFrequency());
    printf("-----------------------------\r\n");
}
void platform_init()
{

    base = EUSCI_B0_BASE;   // Set SPI base address (B0 pins on Radio MSP)

    allow_port_mapping();
//    timerA_init();
    led_init();             // Creates LED data structure
    spiInit();              // Initializes SPI pins on MSP
//    bt_raw_data_init();     // Creates raw data structure for Bluetooth communication
//    bt_UART_init();         // Initializes Bluetooth UART pins on MSP
    print_init_message();

}

void platform_free()
{
    led_free_image();         // Free space used by LED data structure
    led_free_bt_buf();        // Free space used by Bluetooth buffer
}

