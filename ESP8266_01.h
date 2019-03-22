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

void ESP8266_getIP (char dataOut[]);
void ESP8266_getCipStatus (char dataOut[]);
void ESP8266_getListAP (char dataOut[]);
void ESP8266_quitAP (char dataOut[]);
void ESP8266_close (char dataOut[]);
void ESP8266_reset (char dataOut[]);
void ESP8266_setWifiMode (char dataOut[], uint8_t mode);
void ESP8266_init();
