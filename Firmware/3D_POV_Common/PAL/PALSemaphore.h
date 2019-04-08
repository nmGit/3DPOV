/*
 * PALSemaphore.h
 *
 *  Created on: Mar 26, 2019
 *      Author: Noah
 */

#ifndef PAL_PALSEMAPHORE_H_
#define PAL_PALSEMAPHORE_H_

#include "FreeRTOS.h"
#include "semphr.h"
class PALSemaphore
{
public:
        PALSemaphore(bool start_full = false);
        bool take();
        bool tryTake(unsigned timeout_ms);
        void give();
protected:
private:
        bool rtos_take(TickType_t timeout_ticks);
        SemaphoreHandle_t m_handle;
};

#endif /* PAL_PALSEMAPHORE_H_ */
