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


PALThread::PALThread(unsigned priority, unsigned stack_size)
{
    pthread_attr_init(&m_attrs);
    m_priParam.sched_priority = priority;
    m_retc = pthread_attr_setschedparam(&m_attrs, &m_priParam);
    m_retc |= pthread_attr_setdetatchstate(&attrs, PTHREAD_CREATE_DETATCHED);
    m_retc |= pthread_attr_setstacksize(&m_attrs, stack_size);
}

bool PALThread::Start()
{
    m_retc = pthread_create(&m_thread, &m_attrs, Task_handler, NULL);
}

void PALThread::Task_handler()
{
    uint8_t dummy_data = 0;
    Task();
    pthread_exit(&dummy_data);
    delete this;
}

void PALThread::Task()
{

}

