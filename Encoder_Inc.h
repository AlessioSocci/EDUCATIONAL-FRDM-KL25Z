/*
 * Encoder_Inc.h
 *
 *  Created on: 20 lug 2019
 *      Author: Alessio
 */

#ifndef ENCODER_INC_H_
#define ENCODER_INC_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "time.h"

extern uint8_t x1;

void encoder_init(void);

#endif /* ENCODER_INC_H_ */
