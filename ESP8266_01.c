/*
 * ESP8266_01.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "ESP8266_01.h"


char AT_joinAP[]  = "AT+CWJAP=\r"; 			// Parameters: <ssid> ---- ssid, <pwd> ---- wifi password.
char AT_setAP[]  = "AT+CWSAP=\r"; 			// Parameters: <ssid> ---- ssid, <pwd> ---- wifi password, <chl> ---- channel, <ecn> ---- encryption.

char AT_cipMux[]  = "AT+ CIPMUX\r"; 		// Parameters: <mode> ---- 0 = single connection, 1 = multiple connection.
char AT_cipStart[]  = "AT+CIPSTART=\r"; 	// Parameters:
											// if CIPMUX <mode> = 0 -> <type> ---- <length>, <addr> ---- IP address , <port> ---- port.
											// if CIPMUX <mode> = 1 -> <id> ---- 0 - 4 , <type> ---- TCP/UDP, <addr> ---- IP address , <port> ---- port.
char AT_cipSend[]  = "AT+CIPSEND=\r";		// Parameters:
											// if CIPMUX <mode> = 0 -> <length> ---- .
											// if CIPMUX <mode> = 1 ->  <id> ---- 0 - 4, <length> ---- .

char AT_cipServer[]  = "AT+ CIPSERVER=\r"; 	// Parameters: <mode> --- 0 = close server, 1 = open server


void UART_send(uint8_t dataOut)
{
	 while(!((UART1->S1) & (1 << 7)))
	 {

	 }
	 UART1->D = dataOut;
}

void UART_send_AT_command(char command[])
{
	uint8_t i = 0;
	while(command[i] != 13)
	{
		i++;
	}

	for (int j=0; j < i; j++)
	{
		UART_send (command[j]);
	}
}

void UART_send_AT_CarriageReturn_LineFeed(void)
{
	UART_send ('\r');
	UART_send ('\n');
}

void UART_send_AT_value(char value[])
{
	uint8_t i = 0;
	while(value [i] != 13)
	{
		i++;
	}

	for (int j=0; j < i; j++)
	{
		UART_send (value[j]);
	}
}

void UART_getMessage(char dataIn[])
{
	uint8_t i = 0;

	uint32_t timeOut = ticks + 1000;
	while(timeOut > ticks)
	{
		if((UART1->S1) & (1 << 5))
		{
			while(!((UART1->S1) & (1 << 5)));
			dataIn[i] = UART1->D;
			if ((i != 0) && (dataIn[i] =='\n'))
			{
				return;
			}
			i++;
		}
	}
}

void ESP8266_getIP (char dataOut[])
{
	char AT_getIP[]  = "AT+CIFSR\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	UART_send_AT_command(AT_getIP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);
	UART_getMessage(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn3[i] != '\r')
	{
		 dataOut[j] = dataIn3[i];
		 i++;
		 j++;
	}
}

void ESP8266_getCipStatus (char dataOut[])
{
	char AT_cipStatus[]  = "AT+CIPSTATUS\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_command(AT_cipStatus);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
}

void ESP8266_getListAP (char dataOut[])
{
	char AT_listAP[]  = "AT+CWLAP\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_command(AT_listAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
}

void ESP8266_quitAP (char dataOut[])
{
	char AT_quitAP[]  = "AT+CWQAP\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_command(AT_quitAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
}

void ESP8266_close (char dataOut[])
{
	char AT_cipClose[]  = "AT+CIPCLOSE\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_command(AT_cipClose);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
}

void ESP8266_reset (char dataOut[])
{
	char AT_reset[] = "AT+RST\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	delay(10);

	UART_send_AT_command(AT_reset);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 1;
	while (dataIn2[i] != '\r')
	{
		 dataOut[j] = dataIn2[i];
		 i++;
		 j++;
	}
}

void ESP8266_setWifiMode (char dataOut[], uint8_t mode)
{
	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	if (mode == 1)
	{
		char AT_wifiMode[]  = "AT+CWMODE=1\r"; // 1 = Sta
		delay(10);
		UART_send_AT_command(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (mode == 2)
	{
		char AT_wifiMode[]  = "AT+CWMODE=2\r"; // 2 = AP
		delay(10);
		UART_send_AT_command(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (mode == 3)
	{
		char AT_wifiMode[]  = "AT+CWMODE=3\r"; // 3 = both
		delay(10);
		UART_send_AT_command(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else
	{
		UART_getMessage(dataIn1);
		UART_getMessage(dataIn2);
		return;
	}

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);
	UART_getMessage(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_init()
{
	PORTE->PCR[0] |= (1 << 9) | (1 << 8); // ALT3 Mmode UART1 TX
 	PORTE->PCR[1] |= (1 << 9) | (1 << 8); // ALT3 Mmode UART1 RX

 	SIM->SCGC4 |= (1 << 11); // UART1 clock enable

 	UART1->BDH &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

 	UART1->BDL |= (1 << 3) | (1 << 2) | (1 << 0); // 13 = 115200 Baud Rate -> BDH_BDL = BUSCLK / 16 * 115200

 	UART1->C2 |= (1 << 3) | (1 << 2); // TX and RX enable

 	char dataIn1[100] = "";
 	char dataIn2[100] = "";
 	char dataIn3[100] = "";

	UART_send ('A');
	UART_send ('T');

	UART_send ('\r');
	UART_send ('\n');

	UART_getMessage(dataIn1);
	UART_getMessage(dataIn2);
	UART_getMessage(dataIn3);

	delay(10);
}


