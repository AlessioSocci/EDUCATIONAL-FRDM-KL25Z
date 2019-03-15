/*
 * time.h
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#ifndef TIME_H_
#define TIME_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"

extern uint32_t ticks;

typedef struct
{
	uint32_t LDVAL;
	uint32_t CVAL;
	uint32_t TCTRL;
	uint32_t TFLAG;
} Pit_Ch;

#define PIT_CH ((Pit_Ch *) 0x40037100)


void PIT_IRQHandler(void);
void pit_init(void);
void delay (uint16_t mseconds);

#endif /* TIME_H_ */
