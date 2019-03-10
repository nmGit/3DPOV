
#include <DebugUART.h>
#include <stdio.h>

#include <cstring>
#include "UART/UART.h"
#include "ti/drivers/GPIO.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Board.h"
#include <stdarg.h>
#include "UART/UART.h"

/* Override printf */
/*
extern UART_Handle dbguart;
extern UART_Params dbguartParams;
*/

int dbg_printf(const char * format, ...)
{
    // Loop forever echoing
    char *format_char;
    unsigned int i;
    char *s;
    va_list arg;
    va_start(arg, format);

    char buf[DBG_PRINTF_CONVERT_BUFFER_SIZE] = {0};

    for(format_char = const_cast<char *>(format); *format_char != '\0'; format_char++)
    {
        while(*format_char != '%')
        {
            dbg_uart_write(format_char, 1);

            if(*format_char == 0)
            {
                return 0;
            }
            format_char++;

        }
        format_char++;
        switch(*format_char)
        {
        case 'c': i = va_arg(arg, int);
                  dbg_uart_write((char*)&i, 1);
                  break;

        case 'd': i = va_arg(arg, int);
                  if(i < 0)
                  {
                      i = -i;
                      dbg_uart_write("-", 1);
                  }
                  convert(i,10, buf);
                  dbg_uart_write(buf, strlen(buf));
                  break;

        case 's': s = va_arg(arg, char *);
                  dbg_uart_write(buf, strlen(buf));
                  break;
        case 'x': i = va_arg(arg, unsigned int);
                  convert(i,16, buf);
                  dbg_uart_write(buf, strlen(buf));
                  break;
        }

    }


    va_end(arg);
#ifdef NAM
    while (1) {

        UART_read(dbguart, &input, 1);


    }
#endif //NAM

}

void dbg_uart_write(const char * buf, unsigned len)
{
    for(int chr = 0; chr < len; chr++)
    {
        putc_dbg(buf[chr]);
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
    }while(num != 0);

    memcpy(buf, ptr, len);
    return;


}

