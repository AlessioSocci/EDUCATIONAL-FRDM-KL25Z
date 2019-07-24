/*
 * ESP8266_01.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "ESP8266_01.h"

char dataOutFromESP[1000] = "";

char AT_cipStart[]  = "AT+CIPSTART=\r"; 	// Parameters:
											// if CIPMUX <mode> = 0 -> <type> ---- <length>, <addr> ---- IP address , <port> ---- port.
											// if CIPMUX <mode> = 1 -> <id> ---- 0 - 4 , <type> ---- TCP/UDP, <addr> ---- IP address , <port> ---- port.

void Clear_charVector(void)
{
	for(uint16_t i = 0; i < 1000; i++)
	{
		dataOutFromESP[i] = ' ';
	}
}

void UART_send(uint8_t dataOut)
{
	 while(!((UART1->S1) & (1 << 7)))
	 {

	 }
	 UART1->D = dataOut;
}

void UART_send_AT_message(char message[])
{
	uint8_t i = 0;
	while(message[i] != 13)
	{
		i++;
	}

	for (int j=0; j < i; j++)
	{
		UART_send(message[j]);
	}
}

void UART_send_AT_CarriageReturn_LineFeed(void)
{
	UART_send('\r');
	UART_send('\n');
}

void UART_get_AT_message(char dataIn[])
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

// BASIC function

void ESP8266_reset(char dataOut[])
{
	Clear_charVector();

	char AT_reset[] = "AT+RST\r"; // added char \r how "check point" to counting char

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	delay(10);

	UART_send_AT_message(AT_reset);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);

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

void ESP8266_queryGetIP(char dataOut[])
{
	Clear_charVector();

	char AT_getIP[]  = "AT+CIFSR\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	UART_send_AT_message(AT_getIP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

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

void ESP8266_queryGetCipStatus(char dataOut[])
{
	Clear_charVector();

	char AT_cipStatus[]  = "AT+CIPSTATUS\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_message(AT_cipStatus);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);

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

// Wifi AP fucntion
void ESP8266_queryGetListAP(char dataOut[]) // Only in client or both mode
{
	Clear_charVector();

	char AT_listAP[]  = "AT+CWLAP\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";
	char dataIn4[100] = "";
	char dataIn5[100] = "";
	char dataIn6[100] = "";

	delay(10);

	UART_send_AT_message(AT_listAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);
	UART_get_AT_message(dataIn4);
	UART_get_AT_message(dataIn5);
	UART_get_AT_message(dataIn6);

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
	i = 1;
	while (dataIn4[i] != '\r')
	{
		dataOut[j] = dataIn4[i];
		i++;
		j++;
	}
	i = 1;
	while (dataIn5[i] != '\r')
	{
		dataOut[j] = dataIn5[i];
		i++;
		j++;
	}
	i = 1;
	while (dataIn6[i] != '\r')
	{
		dataOut[j] = dataIn6[i];
		i++;
		j++;
	}
}

void ESP8266_setWifiMode(char dataOut[], Wifi_mode mode)
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	if (mode == sta)
	{
		char AT_wifiMode[]  = "AT+CWMODE=1\r"; // 1 = Station
		delay(10);
		UART_send_AT_message(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (mode == AP)
	{
		char AT_wifiMode[]  = "AT+CWMODE=2\r"; // 2 = AP
		delay(10);
		UART_send_AT_message(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (mode == both)
	{
		char AT_wifiMode[]  = "AT+CWMODE=3\r"; // 3 = both
		delay(10);
		UART_send_AT_message(AT_wifiMode);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else
	{
		UART_get_AT_message(dataIn1);
		UART_get_AT_message(dataIn2);
		return;
	}

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn2[i];
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

void ESP8266_queryWifiMode(char dataOut[])
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	char AT_querySetAP[] = "AT+CWMODE?\r";

	delay(10);
	UART_send_AT_message(AT_querySetAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		dataOut[j] = dataIn1[i];
		i++;
		j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_setAP(char dataOut[], char id[], char pass[], char chl[], char ecn[]) 	// Parameters:
																						// <ssid> ---- ssid, <pwd> ---- wifi password,
																						// <chl> ---- channel
																						// <ecn> ---- encryption: 1 = open, 2 = WPA_PSK, 3 = WPA2_PSK 4 = WPA_WPA2_PSK
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";
	char dataIn4[100] = "";
	char dataIn5[100] = "";
	char dataIn6[100] = "";

	delay(10);

	char AT_setAP[] = "AT+CWSAP=";

	uint8_t i = 0;
	uint8_t j =10;

//	AT_setAP[j] = '"';
//	j++;

	while (id[i] != '\r')
	{
		AT_setAP[j] = id[i];
		i++;
		j++;
	}

//	AT_setAP[j] = '"';
//	j++;
	AT_setAP[j] = ',';
	j++;
//	AT_setAP[j] = '"';
//	j++;

	i = 0;
	while (pass[i] != '\r')
	{
		AT_setAP[j] = pass[i];
		i++;
		j++;
	}

//	AT_setAP[j] = '"';
//	j++;
	AT_setAP[j] = ',';
	j++;

	i = 0;
	while (chl[i] != '\r')
	{
		AT_setAP[j] = chl[i];
		i++;
		j++;
	}
	AT_setAP[j] = ',';

	j++;

	i = 0;
	while (ecn[i] != '\r')
	{
		AT_setAP[j] = ecn[i];
		i++;
		j++;
	}
	AT_setAP[j] = '\r';

	delay(10);
	UART_send_AT_message(AT_setAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);
	UART_get_AT_message(dataIn4);
	UART_get_AT_message(dataIn5);
	UART_get_AT_message(dataIn6);

	i = 1;
	j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn4[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn5[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn6[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_queryGetAPSet(char dataOut[])
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	char AT_querySetAP[] = "AT+CWSAP?\r";

	delay(10);
	UART_send_AT_message(AT_querySetAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		dataOut[j] = dataIn1[i];
		i++;
		j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_joinAP(char dataOut[], char SSID[], char pass[])
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	char AT_joinAP[]  = "AT+CWJAP=                               ";

	uint8_t i = 0;
	uint8_t j = 9;

	while (SSID[i] != '\r')
	{
		AT_joinAP[j] = SSID[i];
		i++;
		j++;
	}
	AT_joinAP[j] = ',';
	i = 0;
	j++;
	while (pass[i] != '\r')
	{
		AT_joinAP[j] = pass[i];
		i++;
		j++;
	}
	AT_joinAP[j] = '\r';

	delay(10);
	UART_send_AT_message(AT_joinAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	i = 1;
	j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
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

void ESP8266_quitAP(char dataOut[])
{
	Clear_charVector();

	char AT_quitAP[]  = "AT+CWQAP\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_message(AT_quitAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);

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

// TCP IP function
void ESP8266_cipClose(char dataOut[])
{
	Clear_charVector();

	char AT_cipClose[]  = "AT+CIPCLOSE=0\r";

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);

	UART_send_AT_message(AT_cipClose);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);

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
}

void ESP8266_setCipMux(char dataOut[], connection_type single_multi)
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	if (single_multi == single)
	{
		char AT_cipMux[]  = "AT+CIPMUX=0\r"; // 0 = single connection
		delay(10);
		UART_send_AT_message(AT_cipMux);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (single_multi == multi)
	{
		char AT_cipMux[]  = "AT+CIPMUX=1\r"; // 1 = multiple connection
		delay(10);
		UART_send_AT_message(AT_cipMux);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else
	{
		UART_get_AT_message(dataIn1);
		UART_get_AT_message(dataIn2);
		return;
	}

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

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

void ESP8266_queryCipMuxSet(char dataOut[])
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	char AT_querySetAP[] = "AT+CIPMUX?\r";

	delay(10);
	UART_send_AT_message(AT_querySetAP);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		dataOut[j] = dataIn1[i];
		i++;
		j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_setCipServer(char dataOut[], server_startStop open_close)
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";
	char dataIn4[100] = "";
	char dataIn5[100] = "";

	delay(10);

	if (open_close == stop)
	{
		char AT_cipServer[]  = "AT+CIPSERVER=0,80\r"; // 0 close server
		delay(10);
		UART_send_AT_message(AT_cipServer);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else if (open_close == start)
	{
		char AT_cipServer[]  = "AT+CIPSERVER=1,80\r"; // 1 open server
		delay(10);
		UART_send_AT_message(AT_cipServer);
		UART_send_AT_CarriageReturn_LineFeed();
	}

	else
	{
		UART_get_AT_message(dataIn1);
		UART_get_AT_message(dataIn2);
		return;
	}

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);
	UART_get_AT_message(dataIn4);
	UART_get_AT_message(dataIn5);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn4[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn5[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_commandCipSend(char dataOut[], char id[], char numberOfByte[]) 	// only in AP or both mode!
																		// Parameters:
																		// if CIPMUX <mode> = 0 -> <length> ---- .
																		// if CIPMUX <mode> = 1 ->  <id> ---- 0 - 4, <length> ---- .
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";
	char dataIn4[100] = "";
	char dataIn5[100] = "";

	delay(10);

	char AT_cipSend[]  = "AT+CIPSEND=								";

	uint8_t i = 0;
	uint8_t j = 11;

	while (id[i] != '\r')
	{
		AT_cipSend[j] = id[i];
		i++;
		j++;
	}
	AT_cipSend[j] = ',';

	j++;

	i = 0;
	while (numberOfByte[i] != '\r')
	{
		AT_cipSend[j] = numberOfByte[i];
		i++;
		j++;
	}
	AT_cipSend[j] = '\r';

	delay(10);
	UART_send_AT_message(AT_cipSend);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);
	UART_get_AT_message(dataIn4);
	UART_get_AT_message(dataIn5);

	i = 1;
	j = 0;

	while (dataIn1[i] != '\r')
	{
		 dataOut[j] = dataIn1[i];
		 i++;
		 j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn4[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn5[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_sendData(char dataIn[])
{
	delay (100);

	UART_send_AT_message(dataIn);

	delay (100);
}

void ESP8266_sendPing(char dataOut[], char ping[])
{
	delay(100);

	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";
	char dataIn3[100] = "";

	delay(10);

	char AT_sendPing[] = "AT+PING=								";

	uint8_t i = 0;
	uint8_t j = 8;

	while (ping[i] != '\r')
	{
		AT_sendPing[j] = ping[i];
		i++;
		j++;
	}

	AT_sendPing[j] = '\r';

	delay(10);
	UART_send_AT_message(AT_sendPing);
	UART_send_AT_CarriageReturn_LineFeed();

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	i = 1;
	j = 0;

	while (dataIn1[i] != '\r')
	{
		dataOut[j] = dataIn1[i];
		i++;
		j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
	while (dataIn3[i] != '\r')
	{
		dataOut[j] = dataIn3[i];
		i++;
		j++;
	}
}

void ESP8266_setDHCP(char dataOut[], Wifi_mode mode, uint8_t enable_disable)
{
	Clear_charVector();

	char dataIn1[100] = "";
	char dataIn2[100] = "";

	delay(10);
	if(enable_disable == 0)
	{
		if (mode == AP)
		{
			char AT_setDHCP[] = "AT+CWDHCP_CUR=0,0\r"; // 1 = AP
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}

		else if (mode == sta)
		{
			char AT_setDHCP[] = "AT+CWDHCP_CUR=1,0\r"; // 2 = Station
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}

		else if (mode == both)
		{
			char AT_setDHCP[] = "AT+CWDHCP_CUR=2,0\r"; // 3 = both
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}
	}
	else
	{
		if (mode == AP)
		{
			char AT_setDHCP[] = "AT+CWDHCP_CUR=1,1\r"; // 1 = AP
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}

		else if (mode == sta)
		{
			char AT_setDHCP[] = "AT+CWDHCP\r"; // 2 = Station
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}

		else if (mode == both)
		{
			char AT_setDHCP[] = "AT+CWDHCP_CUR=3,1\r"; // 3 = both
			delay(10);
			UART_send_AT_message(AT_setDHCP);
			UART_send_AT_CarriageReturn_LineFeed();
		}
	}

	delay(10);

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);

	uint8_t i = 1;
	uint8_t j = 0;

	while (dataIn1[i] != '\r')
	{
		dataOut[j] = dataIn1[i];
		i++;
		j++;
	}
	i = 0;
	while (dataIn2[i] != '\r')
	{
		dataOut[j] = dataIn2[i];
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

	UART_get_AT_message(dataIn1);
	UART_get_AT_message(dataIn2);
	UART_get_AT_message(dataIn3);

	delay(10);
}


void ESP8266_send(char numberOfByte[], char dataIn[]) // numberOfByte[] and dataIn[], must terminate with '\r' character (carriage return)
{
	ESP8266_setCipServer(dataOutFromESP, start);	// before send, connect to WiFi net and browse ESP IP (192.168.4.1)

	ESP8266_commandCipSend(dataOutFromESP,"0\r", numberOfByte);

	ESP8266_sendData(dataIn);

	ESP8266_cipClose(dataOutFromESP);
}

