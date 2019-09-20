/*
 * SSD_1306_OLED.c
 *
 *  Created on: 01 ago 2019
 *      Author: Alessio
 */

#include <SH1106_OLED.h>

// OLED 132 x 64 Driver SH1106
uint8_t SH1106_buffer [SH1106_bufferLenght];
uint8_t SSD1306_data = 0;


void SPI_sendByte(uint8_t data, uint8_t data_command)
{
	delay(5);

	if(data_command == 0) // send command
	{
		GPIOA->PCOR |= (1 << 13);
	}
	else // send data
	{
		GPIOA->PSOR |= (1 << 13);
	}

	while(((SPI0->S) & (1 << 5)) == 0);

	SPI0->D = data;

	while(((SPI0->S) & (1 << 5)) == 0);
}

void SH1106_setPageStart(uint8_t page)
{
	delay(2);

	if(page > 8)
	{
		page = 8;
	}

	switch(page)
	{
		case 0:

			SPI_sendByte(SH1106_SET_PAGE_0_ADDRESS, COMMAND);

		break;

		case 1:

			SPI_sendByte(SH1106_SET_PAGE_1_ADDRESS, COMMAND);

		break;

		case 2:

			SPI_sendByte(SH1106_SET_PAGE_2_ADDRESS, COMMAND);

		break;

		case 3:

			SPI_sendByte(SH1106_SET_PAGE_3_ADDRESS, COMMAND);

		break;

		case 4:

			SPI_sendByte(SH1106_SET_PAGE_4_ADDRESS, COMMAND);

		break;

		case 5:

			SPI_sendByte(SH1106_SET_PAGE_5_ADDRESS, COMMAND);

		break;

		case 6:

			SPI_sendByte(SH1106_SET_PAGE_6_ADDRESS, COMMAND);

		break;

		case 7:

			SPI_sendByte(SH1106_SET_PAGE_7_ADDRESS, COMMAND);

		break;
	}

}

void SH1106_setColumnStart(uint8_t column)
{
	if(column > 132)
	{
		column = 132;
	}

	uint8_t column_low_nibble = column & 0x0F;
	uint8_t column_high_nibble = column & 0XF0;

	SPI_sendByte(SH1106_SET_COLUMN_LOWER_NIBBLE_ADDRESS | column_low_nibble, COMMAND);
	SPI_sendByte(SH1106_SET_COLUMN_HIGHER_NIBBLE_ADDRESS | (column_high_nibble << 4), COMMAND);
}

void SH1106_drawPixel(uint8_t xPos, uint8_t yPos)
{
	uint16_t pos = xPos + ((yPos / 8) * 132);

	SH1106_buffer[pos] |= (1 << (yPos % 8));
}

void SH1106_flushPart(uint8_t xPosStart, uint8_t xPosStop, uint8_t yPosStart, uint8_t yPosStop)
{
	uint16_t pos = 0;

	for (uint16_t y = (yPosStart / 8); y <= (yPosStop / 8); y++)
	{
		SH1106_setColumnStart(xPosStart);

		SH1106_setPageStart(y);

		for (uint16_t x = xPosStart; x < xPosStop; x++)
		{
			pos = x + y * 132;

			SPI_sendByte(SH1106_buffer[pos], DATA);
		}
	}
}

void SH1106_clearAllPixel(void)
{
	for(uint16_t i = 0; i < SH1106_bufferLenght; ++i)
	{
		SH1106_buffer[i] = 0;
	}

	SH1106_flushPart(0, 132, 0, 63);
}

void SH1106_init(void)
{
	// SPI 4-wire (OLED 128x64 driver SSD1306)

	SIM->SCGC4 |= (1 << 22); // CLock on SPI0 Module

	PORTD->PCR[1] = (1 << 9); // SPI SCK (alt2 mode)
	PORTD->PCR[2] = (1 << 9); // SPI MOSI (alt2 mode)
	PORTD->PCR[0] = (1 << 9); // SPI CS (alt2 mode)

	PORTD->PCR[5] = (1 << 8); // Reset (alt1 mode)
	GPIOD->PDDR |= (1 << 5);
	GPIOD->PCOR |= (1 << 5); // Reset on

	PORTA->PCR[13] = (1 << 8); // C/D (alt1 mode)
	GPIOA->PDDR |= (1 << 13);

	SPI0->C1 |= (1 << 6) | (1 << 4) | (1 << 3); // SPI0 Enable in Master Mode, clock polarity: active low (idles high)

	SPI0->BR |= (1 << 0); // Prescaler divisor set as 1, Baud Rate divisor set as 4, so Freq. = bus clock / (8 * ...) = ... [Hz]

	GPIOD->PSOR |= (1 << 5); // switch reset from on (low voltage) to off (high voltage)


	SPI_sendByte(SH1106_DISPLAYOFF, COMMAND);

	SPI_sendByte(SH1106_SETDISPLAYCLK, COMMAND);

	SPI_sendByte(0b11110000, COMMAND);

	SPI_sendByte(SH1106_SEGMENTREMAP_127_to_0, COMMAND);

	SPI_sendByte(SH1106_COMSCANDIRECTION_0_to_N, COMMAND);

	SPI_sendByte(SH1106_SETCONTRAST, COMMAND);

	SPI_sendByte(0xFF, COMMAND);

	SPI_sendByte(SH1106_DISPLAYON, COMMAND);

//	SPI_sendByte(SSD1306_DISPLAYALLON, COMMAND);

	SH1106_clearAllPixel();
}


void SH1106_drawPicture (uint8_t bitmap[SH1106_bufferLenght])
{
	for (uint16_t i = 0; i <= SH1106_bufferLenght; ++i)
	{
		SH1106_buffer[i] = bitmap[i];
	}

	SH1106_flushPart(0, 132, 0, 8);
}

