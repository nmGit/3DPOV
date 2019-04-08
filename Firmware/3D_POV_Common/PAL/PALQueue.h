#ifndef PAL_QUEUE_H
#define PAL_QUEUE_H

#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"

class PALQueue
{
public:
    PALQueue(unsigned length, unsigned item_size);
    bool add(void * item, unsigned timeout_ms = 0);
    bool get(void * item, unsigned timeout_ms = (~(0)));
    bool isEmpty();
    bool isFull();
protected:
private:
    QueueHandle_t m_queue_handle;
    unsigned m_item_size;
    unsigned m_queue_len;
};

#endif // PAL_QUEUE_H
