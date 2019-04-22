/*
 * irq_handlers.h
 *
 *  Created on: April 12, 2019
 *      Author: Cassidy
 */

#ifndef IRQ_HANDLERS_H
#define IRQ_HANDLERS_H
#if __cplusplus
extern "C" {
#endif

volatile bool tx_rdy; // For alerting when the hardware is ready
                      // to transmit more data

void EUSCIA0_IRQHandler(void);

void EUSCIA1_IRQHandler(void);

void EUSCIA2_IRQHandler(void);

//*****************************************************************************
// General IRQ A and B Handlers -- Called by a specific A or B handler
// tx_rdy is set to true and the appropriate interrupt flag is cleared.
//*****************************************************************************
void EUSCIAX_IRQHandler(void);
void EUSCIBX_IRQHandler(void);

#if __cplusplus
}
#endif
#endif //IRQ_HANDLERS_H

