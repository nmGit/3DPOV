#include "debugUart.h"
#include <stdio.h>
#include <ti/drivers/UARTMSP432.h>
/* Override printf */
int dbgprint()
{
    // Loop forever echoing
    while (1) {
        UART_read(uart, &input, 1);
        UART_write(uart, &input, 1);
    }

}
