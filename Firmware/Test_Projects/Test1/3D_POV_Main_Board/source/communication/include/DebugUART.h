/*
 * DebugUART.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Noah
 */

#include <stdio.h>
#include "UARTMSP432.h"
#ifndef SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_
#define SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_

extern UART_Handle dbguart;
extern UART_Params dbguartParams;

#define DBG_PRINTF_CONVERT_BUFFER_SIZE 16

#if __cplusplus
extern "C" {
#endif

    int dbg_printf(char * format, ...);
    char * convert(unsigned int num, int base);

#if __cplusplus
}
#endif

#endif /* SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_ */
