#include <platform_init.h>
#include "UARTMSP432.h"
#include "Board.h"
// NAM
// UART
char        input;
UART_Handle dbguart;
UART_Params dbguartParams;

extern "C" void dbg_UART_init()
{
    // Initialize the UART driver
    UART_init();
    // Create a UART with data processing off
    UART_Params_init(&dbguartParams);
    dbguartParams.writeDataMode = UART_DATA_BINARY;
    dbguartParams.readDataMode = UART_DATA_BINARY;
    dbguartParams.readReturnMode = UART_RETURN_FULL;
    dbguartParams.readEcho = UART_ECHO_OFF;
    dbguartParams.baudRate = 9600;

    // Open an instance of the UART drivers
    dbguart = UART_open(Board_UART0, &dbguartParams);

    if(dbguart == NULL)
    {
        return;
    }

}
void platform_init()
{
    dbg_UART_init();
}
