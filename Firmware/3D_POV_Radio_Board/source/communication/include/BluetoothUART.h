/*
 * BluetoothUART.h
 *
 *  Created on: Apr 2, 2019
 *      Author: Cassidy
 */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "RadioUART.h"

#define TX_PER_LED     4
#define BITS_PER_TX    8
#define TIMEOUT_MS     1000

//*****************************************************************************
// Raw data structure for Bluetooth receiving
//*****************************************************************************
uint32_t** raw_data;    // Raw data structure for LED data over Bluetooth

//*****************************************************************************
// Color data structure
//*****************************************************************************
typedef struct {
    uint8_t red;    // 8bit red data
    uint8_t green;  // 8bit green data;
    uint8_t blue;   // 8bit blue data;
} color_type;

//*****************************************************************************
// Image position data packet for each of the 100 positions in a 360 deg sweep
//*****************************************************************************
typedef struct {
    char msg[4];                // Start message
    uint8_t fin;                //
    uint8_t seq;                // 8bit sequence number
    color_type led_colors[16];  // LED color data
    uint8_t checksum;           // Validity check
} img_pos_packet;



#ifndef SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_
#define SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_

#if __cplusplus
extern "C" {
#endif

    void bt_uart_cmd(void);
    void bt_raw_data_init(void);
    void bt_raw_data_free(void);
    void bt_uart_get_packet(void);
    void bt_uart_get_data(void);
    void bt_uart_get_data_test(void);
    void bt_uart_write(const uint8_t * buf, unsigned len);
    unsigned bt_uart_read(uint8_t * buf, unsigned len, unsigned timeout_ms = TIMEOUT_MS);
    char get_val_bt(unsigned timeout_ms = TIMEOUT_MS);
    void put_val_bt(uint8_t val);

#if __cplusplus
}
#endif


#endif /* SOURCE_COMMUNICATION_INCLUDE_BLUETOOTHUART_H_ */
