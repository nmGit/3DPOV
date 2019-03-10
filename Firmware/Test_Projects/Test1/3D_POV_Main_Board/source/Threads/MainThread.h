/*
 * MainThread.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Noah
 */

#ifndef SOURCE_THREADS_MAINTHREAD_H_
#define SOURCE_THREADS_MAINTHREAD_H_

#include "PAL\PALThread.h"
class MainThread : public PALThread
{
public:
    MainThread(unsigned priority, unsigned stack_size, const char * name);
protected:
    void Task();
private:
};


#endif /* SOURCE_THREADS_MAINTHREAD_H_ */
