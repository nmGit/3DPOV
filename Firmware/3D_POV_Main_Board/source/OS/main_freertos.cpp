/*
 * Copyright (c) 2016-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif
#include "ti/devices/msp432p4xx/inc/msp.h"

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include "PAL\PALThread.h"
#include "Threads\MainThread.h"
/* Example/Board Header files */
#include "Board.h"

/* stdio */
//#include <stdio.h>
//#include <platform_init.h>
#include <DebugUART.h>
extern void *mainThread(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE   1024*4

/*
 *  ======== main ========
 */



int free_rtos_init(void)
{
#ifdef NAM
   pthread_t           thread;
   pthread_attr_t      attrs;
   struct sched_param  priParam;
   int                 retc;
#endif // NAM


#ifdef __ICCARM__
    __iar_Initlocks();
#endif
#ifdef NAM
    //dbg_printf("Booting...\r\n");
    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);

    /* Set priority, detach state, and stack size attributes */
    priParam.sched_priority = 1;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* failed to set attributes */
        while (1) {}
    }

    retc = pthread_create(&thread, &attrs, mainThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1) {}
    }
#endif //NAM
    /////////////////////////////////////////////////////
    // The only thing I think is that directly calling malloc
    // initializes the heap. But the new operator also calls malloc
    // but the new operator seems to not work correctly (constructors are
    // not run).
    malloc(1); // <---- WHY THE HELL DO I NEED THIS  ////
    /////////////////////////////////////////////////////
    MainThread * mainthread = new MainThread(2, 0x400, "Main Thread");
    mainthread->Start();
    printf("Starting scheduler...\r\n");
    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************

extern "C" void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    dbg_printf("FATAL: Malloc failed!");
    while(1)
    {
    }
}



//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
extern "C" void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}


