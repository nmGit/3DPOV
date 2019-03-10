/*
 * DebugUART.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Noah
 */

#include <stdio.h>

#include "UART.h"
#ifndef SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_
#define SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_

#define DBG_PRINTF_CONVERT_BUFFER_SIZE 16

#if __cplusplus
extern "C" {
#endif

    int dbg_printf(const char * format, ...);
    void convert(unsigned int num, int base, char * buf);
    void dbg_uart_write(const char * buf, unsigned len);
    void putc_dbg(char c);

#if __cplusplus
}
#endif

#endif /* SOURCE_COMMUNICATION_INCLUDE_DEBUGUART_H_ */
