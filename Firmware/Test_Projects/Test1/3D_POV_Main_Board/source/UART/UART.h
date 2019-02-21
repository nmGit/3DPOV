/*
 * UART.h
 *
 *  Created on: Feb 20, 2019
 *      Author: Noah
 */

#ifndef SOURCE_UART_UART_H_
#define SOURCE_UART_UART_H_
#include "ti/devices/msp432p4xx/inc/msp.h"

//void uart_init();
void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr);
char uart_a_getc(EUSCI_A_Type * base);
char uart_a_0_ISR();




#endif /* SOURCE_UART_UART_H_ */
