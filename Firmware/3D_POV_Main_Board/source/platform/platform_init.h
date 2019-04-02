/*
 * platform_init.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Noah
 */

#ifndef SOURCE_PLATFORM_PLATFORM_INIT_H_
#define SOURCE_PLATFORM_PLATFORM_INIT_H_

#if __cplusplus
extern "C" {
#endif

    void platform_init();
    void timerA_init(void);
    void print_init_message();
#if __cplusplus
}
#endif



#endif /* SOURCE_PLATFORM_PLATFORM_INIT_H_ */
