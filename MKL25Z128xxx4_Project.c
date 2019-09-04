/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "stdint.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
/* TODO: insert other include files here. */

#include "time.h"
#include "low_power_timer.h"
#include "HW_interrupt.h"
#include "adc.h"
#include "dac.h"
#include "pwm.h"
#include "ESP8266_01.h"
#include "MLX90614.h"
#include "Encoder_Inc.h"
#include "UART-DMX512.h"
#include "SSD1306_OLED_1,3inch.h"

/* TODO: insert other definitions and declarations here. */

// ADC
uint16_t dataADC = 0;

/*
 * @brief   Application entry point.
 */
int main(void)
{
  	/* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();

    SIM->SCGC5 |= (1 << 9); // Clock on PORT A
    SIM->SCGC5 |= (1 << 10); // Clock on PORT B
    SIM->SCGC5 |= (1 << 11); // Clock on PORT C
    SIM->SCGC5 |= (1 << 12); // Clock on PORT D
    SIM->SCGC5 |= (1 << 13); // Clock on PORT E

    // HW interrupt
    HW_interrupt_init();

    // LPTMR
    LPTMR0_init();

    // PIT
    pit_init();

    // ADC
    adc_init();

    // DAC
    dac_init();

	// PWM
	pwm_init();

	// UART --- ESP8266 WiFi transceiver
	ESP8266_init();

	// I2C --- MLX90614 IR thermometer
	MLX90614_init(57600);

	// UART_DMX512
	UART_DMX512_init();

	// Encoder
	encoder_init();

	// SPI --- OLED 128 x 64 SSD1306
	SSD1306_init();

	char dataToWiFi_A[8] = "Socci\r";
	char dataToWiFi_B[8] = "Alessio\r";
	char dataToWiFi_C[28] = "-ch3:000 -ch4:000 -ch5:000 \r";

	float ambientTemp = 0;
	float objectTemp = 0;

	uint8_t dataOut[129];

	for (int i = 0; i < 129; i++)
	{
		dataOut[i] = 0;
	}

	dataOut[0] = 0x0;
	dataOut[1] = 0x5A;
	dataOut[2] = 0x0;
	dataOut[3] = 0x0;
	dataOut[4] = 0x0;
	dataOut[5] = 0x0;

    /* Force the counter to be placed into memory. */
    volatile static int i = 0;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1)
    {
    	if (i == 127)
    	{
    		i=0;
    	}

    	delay(200);


    	if (i==0) // test ESP 8266
    	{
    		ESP8266_queryGetCipStatus(dataOutFromESP);

			ESP8266_setWifiMode(dataOutFromESP, AP);

			ESP8266_queryWifiMode(dataOutFromESP);

			ESP8266_setCipMux(dataOutFromESP, multi);

			ESP8266_queryCipMuxSet(dataOutFromESP);

			/*
			 * FIX THIS!! ...to connect we must insert break execution here with a break point,
			 * connect by an extern client to access point created (http://192.168.4.1) by ESP and resume...
			 * to browse data command an auto-refresh of html page in client device browser
			 */

		// Client Mode operations

//			ESP8266_queryGetListAP(dataOutFromESP);
//
//			ESP8266_setDHCP(dataOutFromESP, sta, 1);
//
//			ESP8266_joinAP(dataOutFromESP, "SSID\r", "password\r");
//
//			ESP8266_queryGetIP(dataOutFromESP);


		// Access Point Mode operations

			ESP8266_send("5\r", dataToWiFi_A);

			delay(5000); // delay time to browse data

			ESP8266_send("7\r", dataToWiFi_B);

			delay(5000); // delay time to browse data
    	}

    	if(i == 2)
    	{
    		SPI_sendByte(SSD1306_SETCOLUMNADDRESS, COMMAND);
    		SPI_sendByte(0, COMMAND);
	 	  	SPI_sendByte(30, COMMAND);

    		SPI_sendByte(SSD1306_SETPAGEADDRESS, COMMAND);
    		SPI_sendByte(0, COMMAND);
    		SPI_sendByte(1, COMMAND);

    		for(int i = 0; i < 120; i++)
    		{
    			SPI_sendByte(0xFF, DATA);
    		}

    		for(int i = 0; i < 9; i++)
    		{
    			SPI_sendByte(0xFF, DATA);
    		}

    		SPI_sendByte(SSD1306_SETCOLUMNADDRESS, COMMAND);
    		SPI_sendByte(0, COMMAND);
    		SPI_sendByte(30, COMMAND);

    		SPI_sendByte(SSD1306_SETPAGEADDRESS, COMMAND);
    		SPI_sendByte(0, COMMAND);
    		SPI_sendByte(1, COMMAND);

    		for(int i = 0; i < (128); i++)
    		{
    			SPI_sendByte(0x0, DATA);
    		}
    	}

    	if ((arrival_task0_flag == 1) && (disable_task0_flag == 0)) // blinking green led to indicate "Operative-System"
    	{
    		uint32_t current_time = ticks;

    		arrival_task0_flag = 0;

    		GPIOB->PTOR |= (1 << 19);

    		burstTime_task0 = ticks - current_time;
    	}

    	if ((arrival_task1_flag == 1) && (disable_task1_flag == 0)) // test ADC and DAC
    	{
    		uint32_t current_time = ticks;

    		arrival_task1_flag = 0;

    		dataADC = adc_read();
    		dacOut(dataADC); // default dac out on PTE30

    		if (dataADC > 255)
    		{
    			dataADC = 255;
    		}

    		ambientTemp = MLX90614_getTemp(MLX90614_SCALE_CELSIUS, MLX90614_REGISTER_LINEARIZED_TAMBIENT);

    		disable_task2_flag = 1;

    		burstTime_task1 = ticks - current_time;
    	}

    	if (arrival_task2_flag == 1 && (disable_task2_flag == 0)) // test MLX90614
    	{
    		uint32_t current_time = ticks;

    		arrival_task2_flag = 0;

    		objectTemp = MLX90614_getTemp(MLX90614_SCALE_CELSIUS, MLX90614_REGISTER_LINEARIZED_TOBJECT1);

    		disable_task1_flag = 1;

    		burstTime_task2 = ticks - current_time;
    	}

    	if (arrival_task3_flag == 1 && (disable_task3_flag == 0)) // read encoder and assign data-frame y in DMX send array
    	{
    		uint32_t current_time = ticks;

    		arrival_task3_flag = 0;

    		dataOut[y] = encoderOut[y]; // copy data from encoder to DMX send array

    		int k = 0; // copy data from DMX send array to WiFi send array

    		if(y == 3) { k = 0; }
    		else if(y == 4) { k = 9; }
    		else if(y == 5) { k = 18; }

    		dataToWiFi_C[k + 5] = (dataOut[y] / 100) + 48;
    		dataToWiFi_C[k + 6] = ((dataOut[y] - ((dataToWiFi_C[k + 5] - 48) * 100)) / 10) + 48;
    		dataToWiFi_C[k + 7] = (dataOut[y] - ((dataToWiFi_C[k + 5] - 48) * 100) - ((dataToWiFi_C[k + 6] - 48) * 10) + 48);

    		burstTime_task3 = ticks - current_time;
    	}

    	if (arrival_task4_flag == 1 && (disable_task4_flag == 0)) // send one DMX packet of 129 frames
    	{
    		uint32_t current_time = ticks;

    		arrival_task4_flag = 0;

    		NVIC->ICER[0] = (1 << 30); // HW interrupt on PTA disable in NVIC (only PIT, can interrupt DMX send routine...)
    									// -- ATTENTION! use with |= operator disable all other interrupts!!

    		UART_DMX512_send(dataOut);

    		NVIC->ISER[0] |= (1 << 30); // HW interrupt on PTA enable in NVIC

    		burstTime_task4 = ticks - current_time;
    	}

    	if (arrival_task5_flag == 1 && (disable_task5_flag == 0)) // send to WiFi
    	{
    		uint32_t current_time = ticks;

    		arrival_task5_flag = 0;

    		ESP8266_send("27\r", dataToWiFi_C);

    		burstTime_task5 = ticks - current_time;
    	}

    	i++ ;
    }

    return 0 ;
}
