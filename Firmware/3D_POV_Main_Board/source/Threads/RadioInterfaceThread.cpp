/*
 * MainThread.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Noah
 */

//#include "PAL/PALThread.h"
//#include <DebugUART.h>
#include "Threads/MainThread.h"
#include "Threads/RadioInterfaceThread.h"
#include "PAL/PALControl.h"
#include "PAL/PALDelay.h"
#include "DebugUART.h"
#include "BluetoothUART.h"
#include "SPI/spi.h"

RadioThread::RadioThread(unsigned priority, unsigned stack_size, const char * name):
    PALThread(priority, stack_size, name)
{

}


uint32_t** data;

/* CMS
 * Test data for communicating though Bluetooth UART protocol.
 *
 * Copied from Radio board SPI test.
 *
 * Want to see if I can send this information over bluetooth
 */
void test_data(void) {

    int i;

    // Allocate memory for the data structure
    data = (uint32_t**) malloc(FINS * LEDS_PER_FIN * sizeof(uint32_t));
    for(i = 0; i < FINS; i++) {
        data[i] = (uint32_t*) malloc(LEDS_PER_FIN * sizeof(uint32_t));
    }

    int r, c;
    for(r = 0; r < FINS; r++) {
        for(c = 0; c < LEDS_PER_FIN; c++) {
            data[r][c] = 0xE2000000;
        }
    }

    // Initialize data
    data[0][0] = (DIM << 24) | MAGENTA;
    data[0][1] = (DIM << 24) | RED;
    data[0][2] = (DIM << 24) | ORANGE;
    data[0][3] = (DIM << 24) | YELLOW;
    data[0][4] = (DIM << 24) | GREEN;
    data[0][5] = (DIM << 24) | CYAN;
    data[0][6] = (DIM << 24) | BLUE;
    data[0][7] = (DIM << 24) | PURPLE;
    data[0][8] = (DIM << 24) | LAVENDER;
    data[0][9] = (DIM << 24) | MAGENTA;
    data[0][10] = (DIM << 24) | RED;
    data[0][11] = (DIM << 24) | ORANGE;
    data[0][12] = (DIM << 24) | YELLOW;
    data[0][13] = (DIM << 24) | GREEN;
    data[0][14] = (DIM << 24) | CYAN;
    data[0][15] = (DIM << 24) | BLUE;

    //data[1][0] = (DIM << 24) | RED;
}

void RadioThread::Task()
{
    dbg_printf("In Radio Thread\r\n");


    // CMS
    // Set up test data
  test_data();

    /* CMS
     * LED data is sent in packets of 32 bits
     * but UART transmits in packets of 8 bits
     */
/*
    int r, c, b;
    uint32_t* fin_data;
    uint32_t led_data;
    uint8_t data_8bit;
    for (r = 0; r < FINS; r++) {
        fin_data = data[r];
        for (c = 0; c < LEDS_PER_FIN; c++){
            led_data = fin_data[c];

            // Send the 32 bit information in 4 chunks of 8 bits
            for (b = 3; b >= 0; b--) {
                // Send in order of highest 8 bits to lowest 8 bits!
                data_8bit = led_data >> (8*b);
                bt_uart_write(&data_8bit, 1);
            }

        }
    }
*/

    char cmd_example = 'H';
    uint8_t value = 80;

    while(1){
      //bt_uart_cmd(&cmd_example, 1000);
      bt_uart_write(&value, 2); // Writing doesn't seem to be working right now?? 4/7



      PALDelay_ms(10);
    }
}


