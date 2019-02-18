
#include <DebugUART.h>
#include <stdio.h>

#include <cstring>
#include "UARTMSP432.h"
#include "ti/drivers/GPIO.h"
#include "Board.h"
#include <stdarg.h>
/* Override printf */
/*
extern UART_Handle dbguart;
extern UART_Params dbguartParams;
*/

int dbg_printf(char * format, ...)
{
    // Loop forever echoing
    char *format_char;
    unsigned int i;
    char *s;
    va_list arg;
    va_start(arg, format);

    char buf[DBG_PRINTF_CONVERT_BUFFER_SIZE] = {0};

    for(format_char = format; *format_char != '\0'; format_char++)
    {
        while(*format_char != '%')
        {
            UART_write(dbguart, format_char, 1);
            format_char++;
            if(format_char == '\0')
            {
                break;
            }


        }
        format_char++;
        switch(*format_char)
        {
        case 'c': i = va_arg(arg, int);
                  UART_write(dbguart, &i, 1);
                  break;

        case 'd': i = va_arg(arg, int);
                  if(i < 0)
                  {
                      i = -i;
                      UART_write(dbguart, "-", 1);
                  }
                  strncpy(buf, convert(i,16), DBG_PRINTF_CONVERT_BUFFER_SIZE);
                  UART_write(dbguart, buf, strlen(buf));
                  break;

        case 's': s = va_arg(arg, char *);
                  UART_write(dbguart, s, strlen(s));
                  break;
        case 'x': i = va_arg(arg, unsigned int);

                  strncpy(buf, convert(i,16), DBG_PRINTF_CONVERT_BUFFER_SIZE);
                  UART_write(dbguart, buf, strlen(buf));
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

char * convert(unsigned int num, int base)
{
    static char Representation[] = "0123456789ABCDEF";

    char *ptr;
    char buffer[DBG_PRINTF_CONVERT_BUFFER_SIZE];
    ptr = buffer + DBG_PRINTF_CONVERT_BUFFER_SIZE;
    *ptr = '\0';

    do
    {
        *--ptr = Representation[num % base];
        num /= base;
    }while(num != 0);

    return(ptr);


}

