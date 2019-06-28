/*
 * UART-RS485.h
 *
 *  Created on: 14 giu 2019
 *      Author: Alessio
 */

#ifndef UART_DMX512_H_
#define UART_DMX512_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "time.h"


void UART_DMX512_init(void);
void UARTdmx_send(uint8_t dataOut);
void UART_DMX512_send(uint8_t dataOut[512]);


#endif /* UART_DMX512_H_ */
