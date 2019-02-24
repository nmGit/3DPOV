/*
 * PALThread.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

#ifndef SOURCE_PAL_PALTHREAD_H_
#define SOURCE_PAL_PALTHREAD_H_



class PALThread()
{
public:
    PALThread(unsigned priority, unsigned stack_size);
    bool Start();
protected:
    void Task();

private:
    pthread_t           m_thread;
    pthread_attr_t      m_attrs;
    struct sched_param  m_priParam;
    int                 m_retc;

    void Task_handler();
}

#endif /* SOURCE_PAL_PALTHREAD_H_ */
