/*
 * ESP8266_01.h
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "time.h"

void UART_send(uint8_t dataOut);
void UART_get(uint8_t* dataIn);
void UART_init();
