/*
 * DataLinkThread.h
 *
 *  Created on: Apr 6, 2019
 *      Author: Noah
 */

#ifndef SOURCE_THREADS_DATALINKTHREAD_H_
#define SOURCE_THREADS_DATALINKTHREAD_H_

#include "PAL\PALThread.h"

class DataLinkThread : public PALThread
{
public:
    DataLinkThread(unsigned priority, unsigned stack_size, const char * name);
protected:
    void Task();
private:
};



#endif /* SOURCE_THREADS_DATALINKTHREAD_H_ */
