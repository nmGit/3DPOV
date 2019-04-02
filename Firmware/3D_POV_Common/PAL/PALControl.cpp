#include "PALControl.h"
#include "FreeRTOS.h"
#include "task.h"

void PALYield()
{
    taskYIELD();
}
