#include "PAL/PALDelay.h"
#include "FreeRTOS.h"
#include "task.h"

void PALDelay_ms(unsigned delay_ms)
{
    TickType_t ticks = delay_ms * (configTICK_RATE_HZ / 1000);

    vTaskDelay(ticks);
}
