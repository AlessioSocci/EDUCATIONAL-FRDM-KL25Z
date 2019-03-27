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

extern char dataOutFromESP[1000];

// BASIC function
void ESP8266_reset(char dataOut[]);
void ESP8266_queryGetIP(char dataOut[]);
void ESP8266_queryGetCipStatus(char dataOut[]);

// Wifi AP fucntion
void ESP8266_queryGetListAP(char dataOut[]);
void ESP8266_setWifiMode(char dataOut[], uint8_t mode);
void ESP8266_queryWifiMode(char dataOut[]);
void ESP8266_setAP(char dataOut[], char id[], char pass[], char chl[], char ecn[]);
void ESP8266_queryGetAPSet(char dataOut[]);
void ESP8266_joinAP(char dataOut[], char SSID[], char pass[]);
void ESP8266_quitAP(char dataOut[]);

// TCP IP function
void ESP8266_cipClose(char dataOut[]);
void ESP8266_setCipMux(char dataOut[], uint8_t single_multi);
void ESP8266_queryCipMuxSet(char dataOut[]);
void ESP8266_setCipServer(char dataOut[], uint8_t open_close);
void ESP8266_cipSend(char dataOut[], char id[], char numberOfByte[]);
void ESP8266_sendData(char dataIn[]);
void ESP8266_sendPing(char dataOut[], char ping[]);

void ESP8266_init();

