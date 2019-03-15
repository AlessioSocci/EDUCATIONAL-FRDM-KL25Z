/*
 * dac.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "dac.h"

void dac_init(void)
{
	// DAC
	SIM->SCGC6 =  SIM->SCGC6 | (1 << 31);

	DAC0->SR = 0; // clear status register

	DAC0->C0 = (1<<7); // enable DAC
}

void dacOut (uint16_t value)
{
	uint8_t msb = 0;
	uint8_t lsb = 0;

	if(value < 4096)
	{
		msb = (uint8_t)(value >> 8);
		lsb = (uint8_t)(value);

		DAC0->DAT->DATH = msb;
		DAC0->DAT->DATL = lsb;
	}
}
