/*
 * ComputerInterfaceThread.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Noah
 */

#ifndef SOURCE_THREADS_COMPUTERTHREAD_H_
#define SOURCE_THREADS_COMPUTERTHREAD_H_

#include "PAL\PALThread.h"
class ComputerInterfaceThread : public PALThread
{
public:
    ComputerInterfaceThread(unsigned priority, unsigned stack_size, const char * name);
protected:
    void Task();
private:
};


#endif /* SOURCE_THREADS_COMPUTERTHREAD_H_ */
