/*
 * processor_init.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */
#include "Proc/processor_init.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>

void init_clocks()
{

    // For  UART
        // Map pins to uart
        CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    //    CS->CTL0 = 0;                         // Reset tuning parameters
    //    CS->CTL0 = CS_CTL0_DCORSEL_3;         // Set DCO to 12MHz (nominal, center of 8-16MHz range)
        CS->CTL1 = CS_CTL1_SELA_2 |             // Select ACLK = REFO
                   CS_CTL1_SELS_3;              // SMCLK = DCO
    //             CS_CTL1_SELM_3;              // MCLK = DCO
     // CS->KEY = 0;                            // Lock CS module from unintended accesses

    /* Halting the Watchdog */
   // MAP_WDT_A_holdTimer();

    /* Configuring pins for peripheral/crystal usage and LED for output */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
   // MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Setting the external clock frequency. This API is optional, but will
     * come in handy if the user ever wants to use the getMCLK/getACLK/etc
     * functions
     */
    CS_setExternalClockSourceFrequency(32000,48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    CS_startHFXT(false);

    /* Initializing MCLK to HFXT (effectively 48MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Configuring SysTick to trigger at 24000000 (MCLK is 48MHz so this will
     * make it toggle every 0.5s) */
    //MAP_SysTick_enableModule();
   // MAP_SysTick_setPeriod(48000000/1000);
   // MAP_Interrupt_enableSleepOnIsrExit();
    //MAP_SysTick_enableInterrupt();

    /* Enabling MASTER interrupts */
    //MAP_Interrupt_enableMaster();




}

void disable_wdt()
{
    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
            WDT_A_CTL_HOLD;
}
void processor_init()
{
    init_clocks();
}


