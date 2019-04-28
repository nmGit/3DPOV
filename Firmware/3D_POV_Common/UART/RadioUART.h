/*
 * RadioUART.h
 *
 *  Created on: April 12, 2019
 *      Author: Cassidy
 */

#ifndef SOURCE_UART_UART_H_
#define SOURCE_UART_UART_H_

#define RX_BUF_SIZE 2048

#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>
#include <cstring>

//void uart_init();
void uart_a_submit_for_transmit(EUSCI_A_Type * base, char chr);
uint8_t uart_a_getc(EUSCI_A_Type * base, char * c, unsigned timeout_ms = 100);
char uart_a_1_ISR();
bool read_line(char* buffer, unsigned max_len);
char uart_a_1_rcvd_chr;

#endif /* SOURCE_UART_UART_H_ */
