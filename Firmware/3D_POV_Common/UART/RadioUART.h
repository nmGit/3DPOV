/*
 * RadioUART.h
 *
 *  Created on: April 12, 2019
 *      Author: Cassidy
 */

#ifndef SOURCE_UART_UART_H_
#define SOURCE_UART_UART_H_

#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>

//void uart_init();
void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr);
uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms = 100);
char uart_a_1_ISR();

char uart_a_1_rcvd_chr;

#endif /* SOURCE_UART_UART_H_ */
