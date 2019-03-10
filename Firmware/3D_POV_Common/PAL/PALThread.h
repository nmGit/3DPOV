/*
 * PALThread.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */
#include <FreeRTOS.h>
#include <task.h>
#include <pthread.h>

#ifndef SOURCE_PAL_PALTHREAD_H_
#define SOURCE_PAL_PALTHREAD_H_


#define PALTHREAD_MAX_NAME_LENGTH 128

class PALThread
{
public:
    PALThread(unsigned priority, unsigned stack_size, const char * name);
    bool Start();
    static void Task_handler(void * arg0);
    virtual void Task();
protected:


private:
    pthread_t           m_thread;
    pthread_attr_t      m_attrs;
    struct sched_param  m_priParam;
    int                 m_retc;

    unsigned            m_priority;
    unsigned            m_stack_size;
    TaskHandle_t        m_handle;
    char                m_name[PALTHREAD_MAX_NAME_LENGTH];

};

#endif /* SOURCE_PAL_PALTHREAD_H_ */
