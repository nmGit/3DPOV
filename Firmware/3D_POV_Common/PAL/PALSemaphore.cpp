/*
 * PALSemaphore.cpp
 *
 *  Created on: Mar 26, 2019
 *      Author: Noah
 */
#include <stdint.h>
#include "PALSemaphore.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include <assert.h>
#include "Proc/processor_tools.h"
#include "platform/platform_tools.h"

PALSemaphore::PALSemaphore(bool start_full)
{
    m_handle = xSemaphoreCreateBinary();

    if(start_full)
    {
        give();
    }
}

bool PALSemaphore::take()
{
    // Make sure the semaphore has been initialized
    assert(m_handle != nullptr);

    BaseType_t result;

    result = xSemaphoreTake(m_handle, portMAX_DELAY);

    if(result == pdPASS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PALSemaphore::tryTake(unsigned timeout_ms)
{
    // configTICK_RATE_HZ is the number of ticks in a second
    unsigned num_ticks = ms_to_ticks(timeout_ms);

    return rtos_take(num_ticks);
}

// Not an API function
bool PALSemaphore::rtos_take(TickType_t timeout_ticks)
{
    BaseType_t result;
    if(!interruptActive())
    {
        result = xSemaphoreTake(m_handle, timeout_ticks);
    }
    else
    {
        // You should NEVER try to take a semaphore from within an ISR
        // ISRs are not tasks and can not be blocked.
        assert(false);
    }

    if(result == pdPASS)
    {
       return true;
    }
    else
    {
       return false;
    }

}
void PALSemaphore::give()
{
    // Was a there a higher priority task other than the one which was just blocked
    // also trying to take the same semaphore? xHigherPriorityTaskWoken holds the answer.
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    if(!interruptActive())
    {
        xSemaphoreGive(m_handle);
    }
    else
    {
        xSemaphoreGiveFromISR(m_handle, &xHigherPriorityTaskWoken);
    }

}


