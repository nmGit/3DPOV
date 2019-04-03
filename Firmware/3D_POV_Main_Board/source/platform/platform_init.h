/*
 * platform_init.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Noah & Joe
 */

#ifndef SOURCE_PLATFORM_PLATFORM_INIT_H_
#define SOURCE_PLATFORM_PLATFORM_INIT_H_

#define PWM_WRAP_VAL 0x3AD6
#define ESC_ZERO_PCT_PWR 0x2E6

//#define PWM_WRAP_VAL 0x28E
//#define ESC_ZERO_PCT_PWR 0x20

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
