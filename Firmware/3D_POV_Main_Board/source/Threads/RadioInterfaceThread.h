/*
 * RadioInterfaceThread.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Noah
 */

#ifndef SOURCE_THREADS_RADIOTHREAD_H_
#define SOURCE_THREADS_RADIOTHREAD_H_

#include "PAL\PALThread.h"
class RadioThread : public PALThread
{
public:
    RadioThread(unsigned priority, unsigned stack_size, const char * name);
protected:
    void Task();
private:
};



#endif /* SOURCE_THREADS_RADIOTHREAD_H_ */
