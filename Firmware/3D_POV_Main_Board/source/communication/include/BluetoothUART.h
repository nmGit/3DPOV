/*
 * BluetoothUART.h
 *
 *  Created on: Apr 2, 2019
 *      Author: Cassidy
 */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "UART/UART.h"

#ifndef SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_
#define SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_

#if __cplusplus
extern "C" {
#endif

    void bt_enter_cmd_mode(void);
    void bt_exit_cmd_mode(void);
    void bt_uart_cmd(void);
    void bt_uart_send_data(uint32_t ** data);
    void bt_uart_write(const uint8_t * buf, unsigned len);
    unsigned bt_uart_read(uint8_t * buf, unsigned len, unsigned timeout_ms = 1000);
    char get_val_bt(unsigned timeout_ms = 1000);
    void put_val_bt(uint8_t val);

#if __cplusplus
}
#endif


#endif /* SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_ */
