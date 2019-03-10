/*
 * PALThread.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */
#include "PAL\PALThread.h"
#include <FreeRTOS.h>
#include <task.h>
#include <pthread.h>
#include <cstring>


PALThread::PALThread(unsigned priority, unsigned stack_size, const char * name)
{
#ifdef NAM
    pthread_attr_init(&m_attrs);
    m_priParam.sched_priority = priority;
    m_retc = pthread_attr_setschedparam(&m_attrs, &m_priParam);
    m_retc |= pthread_attr_setdetachstate(&m_attrs, PTHREAD_CREATE_DETACHED);
    m_retc |= pthread_attr_setstacksize(&m_attrs, stack_size);
#endif // NAM
    m_priority = priority;
    m_stack_size = stack_size;
    strncpy(m_name, name, PALTHREAD_MAX_NAME_LENGTH);
}
void PALThread::Task_handler(void * arg0)
{
    uint8_t dummy_data = 0;
    static_cast<PALThread *>(arg0)->Task();
    //pthread_exit(&dummy_data);
    delete arg0;
}
bool PALThread::Start()
{

     unsigned cond_code = xTaskCreate(
                Task_handler,
                m_name,
                m_stack_size,
                this,
                m_priority,
                &m_handle);
     if(cond_code == pdPASS)
     {
         return true;
     }
     else
     {
         return false;
     }
#ifdef NAM
    m_retc = pthread_create(&m_thread, &m_attrs, Task_handler, NULL);
#endif //NAM

}



void PALThread::Task()
{

}

