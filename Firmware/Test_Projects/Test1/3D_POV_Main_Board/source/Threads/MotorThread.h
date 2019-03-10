/*
 * MotorThread.h
 *
 *  Created on: Feb 25, 2019
 *      Author: Noah
 */

#ifndef SOURCE_THREADS_MOTORTHREAD_H_
#define SOURCE_THREADS_MOTORTHREAD_H_

#include "PAL\PALThread.h"
class MotorThread : public PALThread
{
public:
    MotorThread(unsigned priority, unsigned stack_size, const char * name);
protected:
    void Task();
private:
};



#endif /* SOURCE_THREADS_MOTORTHREAD_H_ */
