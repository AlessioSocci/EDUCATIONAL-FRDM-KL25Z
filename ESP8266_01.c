/*
 * ESP8266_01.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "ESP8266_01.h"


void UART_send(uint8_t dataOut)
{
	 while (!((UART1->S1) & (1 << 7)))
	 {

	 }
	 UART1->D = dataOut;
}

void UART_get(uint8_t* dataIn)
{
	uint32_t timeOut = ticks + 200;
	while (timeOut > ticks)
	{
		if ((UART1->S1) & (1 << 5))
		{
			while(!((UART1->S1) & (1 << 5)));
			*dataIn = UART1->D ;
		}
	}
}

void UART_init()
{
	PORTE->PCR[0] |= (1 << 9) | (1 << 8); // ALT3 Mmode UART1 TX
 	PORTE->PCR[1] |= (1 << 9) | (1 << 8); // ALT3 Mmode UART1 RX

 	SIM->SCGC4 |= (1 << 11); // UART1 clock enable

 	UART1->BDH &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

 	UART1->BDL |= (1 << 3) | (1 << 2) | (1 << 0); // 13 = 115200 Baud Rate -> BDH_BDL = BUSCLK / 16 * 115200

 	UART1->C2 |= (1 << 3) | (1 << 2); // TX and RX enable
}
