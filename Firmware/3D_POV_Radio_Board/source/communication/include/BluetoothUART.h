/*
 * BluetoothUART.h
 *
 *  Created on: Apr 2, 2019
 *      Author: Cassidy
 */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "RadioUART.h"
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>

#define BYTES_PER_TX   1
#define BITS_PER_TX    8


#ifndef SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_
#define SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_

#if __cplusplus
extern "C" {
#endif

    void bt_uart_write(const uint8_t * buf, unsigned len);
    unsigned bt_uart_read(uint8_t * buf, unsigned len);
    char get_val_bt(void);
    void put_val_bt(uint8_t val);

#if __cplusplus
}
#endif


#endif /* SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_ */
