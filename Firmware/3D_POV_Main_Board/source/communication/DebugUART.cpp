#include <DebugUART.h>
#include <stdio.h>

#include <cstring>
#include "UART/UART.h"
#include "PAL/PALQueue.h"
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"
#include <stdarg.h>
#include "UART/UART.h"
#include "DataLink/datalink_tools.h"
/* Override printf */
/*
 extern UART_Handle dbguart;
 extern UART_Params dbguartParams;
 */

extern PALSemaphore * dbg_msg_mutex;

int dbg_printf(const char * format, ...)
{
    // Loop forever echoing
    char *format_char;
    int i;
    va_list arg;
    va_start(arg, format);

    char buf[DBG_PRINTF_CONVERT_BUFFER_SIZE] = { 0 };
    dbg_msg_mutex->take();
    for (format_char = const_cast<char *>(format); *format_char != '\0';
            format_char++)
    {
        while (*format_char != '%')
        {

            submit_for_transmit_to_computer(format_char, 1);
            //dbg_uart_write(format_char, 1);
            if (*format_char == 0)
            {
                dbg_msg_mutex->give();
                return 0;
            }
            format_char++;

        }
        format_char++;
        switch (*format_char)
        {
        case 'c':
            i = va_arg(arg, int);
            submit_for_transmit_to_computer(buf, strlen(buf));
            //dbg_uart_write((char*)&i, 1);
            break;

        case 'd':
            i = va_arg(arg, int);
            if (i < 0)
            {
                i = -i;
                dbg_uart_write("-", 1);
            }
            convert(i, 10, buf);
            submit_for_transmit_to_computer(buf, strlen(buf));
            // dbg_uart_write(buf, strlen(buf));
            break;

        case 's':

            submit_for_transmit_to_computer(buf, strlen(buf));
            // dbg_uart_write(buf, strlen(buf));
            break;
        case 'x':
            i = va_arg(arg, unsigned int);
            convert(i, 16, buf);
            submit_for_transmit_to_computer(buf, strlen(buf));
            //dbg_uart_write(buf, strlen(buf));
            break;
        }

    }
    dbg_msg_mutex->give();
    va_end(arg);
    return 0;
#ifdef NAM
    while (1)
    {

        UART_read(dbguart, &input, 1);

    }
#endif //NAM

}

void dbg_uart_write(const char * buf, unsigned len)
{
    for (int chr = 0; chr < len; chr++)
    {
        putc_dbg(buf[chr]);
    }
}

// buf: buffer to read into
// len: length of buffer (exceeding this would be out of bounds for the buffer)
// returns: Number of characters received
unsigned dbg_readLine(char * buf, unsigned len, unsigned timeout_ms)
{
    unsigned pos = 0;
    while (pos == 0 || (buf[pos - 1] != '\r' && pos < len))
    {

        buf[pos] = getc_dbg(timeout_ms);
        if (buf[pos] == '\0')
        {
            break;
        }
        pos++;
    }
    buf[pos] = '\0'; // Null terminate that shit
    return pos;
}

static char rx_c;
char getc_dbg(unsigned timeout_ms)
{
    if (uart_a_getc(EUSCI_A0, &rx_c, timeout_ms))
    {
        return rx_c;
    }
    else
    {
        return '\0';
    }

}

void putc_dbg(char c)
{
    uart_a_submit_for_transmit(EUSCI_A0, c);
    //EUSCI_A0->TXBUF = c;
}

void convert(unsigned int num, int base, char * buf)
{
    static char Representation[] = "0123456789ABCDEF";

    char *ptr;
    char buffer[DBG_PRINTF_CONVERT_BUFFER_SIZE];
    unsigned len = 0;
    ptr = buffer + DBG_PRINTF_CONVERT_BUFFER_SIZE - 1;

    len++;
    *ptr = '\0';

    do
    {
        len++;
        ptr--;
        *ptr = Representation[num % base];
        num /= base;
    }
    while (num != 0);

    memcpy(buf, ptr, len);
    return;

}

