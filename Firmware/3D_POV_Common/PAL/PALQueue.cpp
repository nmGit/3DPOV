#include "PAL/PALQueue.h"
#include "platform/platform_tools.h"
#include <assert.h>
#include "Proc/processor_tools.h"

PALQueue::PALQueue(unsigned length, unsigned item_size)
{
    /* You dun fucked up if this fails. Don't try creating objects
     * when inside interrupt handling mode.
     */
    //   assert(!interruptActive());
    m_item_size = item_size;
    m_queue_len = length;
    m_queue_handle = xQueueCreate(length, item_size);

    /* Somethin be fucked if this fails. Maybe run out of heap? Shiiiit */
    assert(m_queue_handle != nullptr);

}

/* FUNCTION add
 * ARGS: item: Item to add
 *       timeout_ms: the timeout for waiting until a spot opens up if queue is full
 * RETURN: true: success, false: fail
 */
bool PALQueue::add(void * item, unsigned timeout_ms)
{

    BaseType_t result;
    BaseType_t higher_priority_task_woken;
    if (interruptActive())
    {
        result = xQueueSendToBackFromISR(m_queue_handle, item,
                                         &higher_priority_task_woken);
    }
    else
    {
        result = xQueueSendToBack(m_queue_handle, item,
                                  ms_to_ticks(timeout_ms));
    }
    if (result == pdPASS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* FUNCTION: get
 * ARGS: item: The item to populate
 *       timeout_ms: The timeout for waiting for an item if the queue is empty
 * RETURN: true: success, false: fail
 */
bool PALQueue::get(void * item, unsigned timeout_ms)
{
    BaseType_t result;
    BaseType_t higher_priority_task_woken;
    if (interruptActive())
    {
        result = xQueueReceiveFromISR(m_queue_handle, item,
                                      &higher_priority_task_woken);
    }
    else
    {
        result = xQueueReceive(m_queue_handle, item, ms_to_ticks(timeout_ms));
    }
    if (result == pdPASS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* FUNCTION: isEmpty
 * RETURN: True: queue is empty, False: queue is not empty
 */
bool PALQueue::isEmpty()
{

    if (interruptActive())
    {
        BaseType_t result;
        result = xQueueIsQueueEmptyFromISR(m_queue_handle);
        return (result != pdFALSE);
    }
    else
    {
        UBaseType_t result;
        result = uxQueueMessagesWaiting(m_queue_handle);
        return (result == 0);
    }

}

/* FUNCTION: isFull
 * RETURN: True: queue is full, False: queue is not full
 */
bool PALQueue::isFull()
{

    if (interruptActive())
    {
        BaseType_t result;
        result = xQueueIsQueueFullFromISR(m_queue_handle);
        return (result != pdFALSE);
    }
    else
    {
        UBaseType_t result;
        result = uxQueueMessagesWaiting(m_queue_handle);
        return ((unsigned) result == m_queue_len);
    }

}
