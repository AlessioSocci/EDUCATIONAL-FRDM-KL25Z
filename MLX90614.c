/*
 * MLX90614.c
 *
 *  Created on: 19 mar 2019
 *      Author: Alessio
 */

#include "MLX90614.h"

uint16_t value = 0;
uint8_t internalState = 0;

uint8_t low = 0, high = 0, pec = 0;

static uint16_t icrTab[] =
{
    /* 00 */   20, /* 01 */   22, /* 02 */   24, /* 03 */   26,
    /* 04 */   28, /* 05 */   30, /* 06 */   34, /* 07 */   40,
    /* 08 */   28, /* 09 */   32, /* 0A */   36, /* 0B */   40,
    /* 0C */   44, /* 0D */   48, /* 0E */   56, /* 0F */   68,

    /* 10 */   48, /* 11 */   56, /* 12 */   64, /* 13 */   72,
    /* 14 */   80, /* 15 */   88, /* 16 */  104, /* 17 */  128,
    /* 18 */   80, /* 19 */   96, /* 1A */  112, /* 1B */  128,
    /* 1C */  144, /* 1D */  160, /* 1E */  192, /* 1F */  240,

    /* 20 */  160, /* 21 */  192, /* 22 */  224, /* 23 */  256,
    /* 24 */  288, /* 25 */  320, /* 26 */  384, /* 27 */  480,
    /* 28 */  320, /* 29 */  384, /* 2A */  448, /* 2B */  512,
    /* 2C */  576, /* 2D */  640, /* 2E */  768, /* 2F */  960,

    /* 30 */  640, /* 31 */  768, /* 32 */  896, /* 33 */ 1024,
    /* 34 */ 1152, /* 35 */ 1280, /* 36 */ 1536, /* 37 */ 1920,
    /* 38 */ 1280, /* 39 */ 1536, /* 3A */ 1792, /* 3B */ 2048,
    /* 3C */ 2304, /* 3D */ 2560, /* 3E */ 3072, /* 3F */ 3840,
};

uint8_t crc8Coder(uint8_t inCrc, uint8_t inData)
{
    int8_t i;
    uint8_t data;

    data = inCrc ^ inData;
    for(i = 0; i < 8; i++ )
    {
        if(( data & 0x80 ) != 0 )
        {
            data <<= 1;
            data ^= 0x07;
        }
        else
        {
            data <<= 1;
        }
    }
    return data;
}

void I2C0_IRQHandler(void)
{
	if(internalState == 1)
	{
		if((I2C0->S & (1 << 0)) == 0) // wait to receive ack from slave device
		{
			I2C0->D = MLX90614_REGISTER_LINEARIZED_TAMBIENT;	// send RAM or EEPROM access command
			uint32_t timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete

			delay(10);
			internalState = 10;
		}
		else
		{
			delay(10);
			internalState = 0;
			I2C0->C1 &= ~(1 << 5); // Stop
		}

		I2C0->S |= (1 << 1); // clear interrupt flag

		return;
	}

	if(internalState == 10)
	{
		if((I2C0->S & (1 << 0)) == 0) // wait to receive ack from slave device
		{
			I2C0->C1 &= ~(1 << 4); // change to RX mode
			I2C0->C1 |= (1 << 3); // send not ack

			uint8_t dummyread = 0;
			dummyread = I2C0->D; // dummy read

			uint32_t timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			low = I2C0->D; // read low data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			high = I2C0->D; // read high data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			pec = I2C0->D; // read pec (packet error code) data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			I2C0->C1 &= ~(1 << 5); // Stop

			delay(10);

			uint8_t crc = crc8Coder(0, MLX90614_WRITEADDRESS);
			crc = crc8Coder(crc, MLX90614_REGISTER_LINEARIZED_TAMBIENT);
			crc = crc8Coder(crc, MLX90614_READADDRESS);
			crc = crc8Coder(crc, low);
			crc = crc8Coder(crc, high); // Received PEC control

			delay(10);

			if(crc != pec)
			{
				internalState = 0;
			}

			value = ((high << 8) & 0xFF00) | (low & 0x00FF);
		}
		else
		{
				internalState = 0;
		}

		I2C0->C1 &= ~(1 << 5); // Stop
		I2C0->S |= (1 << 1); // clear interrupt flag

		return;
	}

	if(internalState == 2)
	{
		if((I2C0->S & (1 << 0)) == 0) // wait to receive ack from slave device
		{
			I2C0->D = MLX90614_REGISTER_LINEARIZED_TOBJECT1;	// send RAM or EEPROM access command
			uint32_t timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete

			delay(10);
			internalState = 20;
		}
		else
		{
			delay(10);
			internalState = 0;
			I2C0->C1 &= ~(1 << 5); // Stop
		}

		I2C0->S |= (1 << 1); // clear interrupt flag

		return;
	}

	if(internalState == 20)
	{
		if((I2C0->S & (1 << 0)) == 0) // wait to receive ack from slave device
		{
			I2C0->C1 &= ~(1 << 4); // change to RX mode
			I2C0->C1 |= (1 << 3); // send not ack

			uint8_t dummyread = 0;
			dummyread = I2C0->D; // dummy read

			uint32_t timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			low = I2C0->D; // read low data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			high = I2C0->D; // read high data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			pec = I2C0->D; // read pec (packet error code) data
			timeOut = ticks + 50;
			while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete
			I2C0->C1 &= ~(1 << 3); // send ack

			I2C0->C1 &= ~(1 << 5); // Stop

			delay(10);

			uint8_t crc = crc8Coder(0, MLX90614_WRITEADDRESS);
			crc = crc8Coder(crc, MLX90614_REGISTER_LINEARIZED_TOBJECT1);
			crc = crc8Coder(crc, MLX90614_READADDRESS);
			crc = crc8Coder(crc, low);
			crc = crc8Coder(crc, high); // Received PEC control

			delay(10);

			if(crc != pec)
			{
				internalState = 0;
			}

			value = ((high << 8) & 0xFF00) | (low & 0x00FF);
		}
		else
		{
			internalState = 0;
		}

		I2C0->C1 &= ~(1 << 5); // Stop
		I2C0->S |= (1 << 1); // clear interrupt flag

		return;
	}

	I2C0->S |= (1 << 1); // clear interrupt flag

	return;
}

void MLX90614_init(uint32_t inputBaudRate)
{
	SIM->SCGC4 |= (1 << 6); // I2C0 clock enable
	PORTC->PCR[8] |= (1 << 9); // PTC 8 in Alt 2 mode, as SCL pin
	PORTC->PCR[9] |= (1 << 9); // PTC 9 in Alt 2 mode, as SDA pin

	uint32_t newError;
	uint32_t oldError = 0xFFFF;
	uint8_t resultIcr = 0xFF;
	uint8_t icrTabValue = 0;
	uint32_t resultBaudRate = 0;

	for(icrTabValue = 0; icrTabValue < 64; icrTabValue++) // compute icr value
	{
		resultBaudRate = 25000000 / icrTab[icrTabValue]; // supposing mul fixed to 0

	    newError = inputBaudRate - resultBaudRate;

	    if(newError < oldError)
	    {
	    	oldError = newError;
	    	resultIcr = icrTabValue;
	    }

	    else if(newError > oldError)
	    {
	    	// wrong inputBaudRate
	    }
	}

	uint8_t regValue = resultIcr & 0b00111111;

	I2C0->F = regValue;

//	I2C0->SMB |= (1 << 7);

//	I2C0->C2 |= (1 << 5); // High drive select

	I2C0->C1 |= (1 << 7) | (1 << 6) | (1 << 5)  | (1 << 4); // I2C0 enable, Interrupt enable, Master mode select, TX mode

    NVIC->IP[2] |= (1 << 7); // preemptive priority set as 2; min value is 3, max and default is 0
    NVIC->ISER[0] |= (1 << 8); // interrupt enable in NVIC
}

float convert_To_Temperature(uint16_t value, MLX90614_Scale scale)
{
    float temp = 0.0;

    switch(scale)
    {
    	case MLX90614_SCALE_KELVIN:
    		temp = ((float)value) * 0.02;
        break;

    	case MLX90614_SCALE_CELSIUS:
    		temp = (((float)value) * 0.02) - 273.15;
        break;
    }
    return temp;
}

float MLX90614_getTemp(MLX90614_Scale scale, MLX90614_RAM_Or_EEPROM_Read_Address reg)
{
	if(reg == MLX90614_REGISTER_LINEARIZED_TAMBIENT)
	{
		delay(10);
		internalState = 1;
	}
	else if(reg == MLX90614_REGISTER_LINEARIZED_TOBJECT1)
	{
		delay(10);
		internalState = 2;
	}

	delay(10);

	I2C0->C1 |= (1 << 5) | (1 << 4); // Start
	I2C0->D = MLX90614_WRITEADDRESS; // send slave address

	uint32_t timeOut = ticks + 50;
	while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete

	delay(10);

	I2C0->C1 |= (1 << 2); // repeat start
	I2C0->D = MLX90614_READADDRESS;
	timeOut = ticks + 50;
	while(timeOut > ticks && (I2C0->S & (1 << 7)) == 0); // wait transfer complete

	float temp = convert_To_Temperature (value, scale);

	return temp;
}



