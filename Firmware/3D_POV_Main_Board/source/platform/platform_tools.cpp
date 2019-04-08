#include "platform_tools.h"
#include "FreeRTOS.h"

unsigned ms_to_ticks(unsigned ms)
{
    return ((ms * 1000) / configTICK_RATE_HZ);
}
