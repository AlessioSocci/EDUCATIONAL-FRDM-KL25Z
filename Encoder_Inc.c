/*
 * Encoder_Inc.c
 *
 *  Created on: 20 lug 2019
 *      Author: Alessio
 */

#include "Encoder_Inc.h"
#include "time.h"
uint8_t x1 = 0;

void encoder_init(void)
{
	PORTA->PCR[16] |= (1 << 8) | (1 << 4); // Set Alt 1 mode for GPIO, passive filter on
	PORTA->PCR[17] |= (1 << 8) | (1 << 4); // Set Alt 1 mode for GPIO, passive filter on

	GPIOA->PDDR &= ~(1 << 16);  // PORTD pin 6 set as input
	GPIOA->PDDR &= ~(1 << 17);  // PORTD pin 7 set as input

	PORTA->PCR[16] |= (1 << 19) | (1 << 17);  // interrupt configuration on PORTA pin 16, on rising edge
	PORTA->PCR[16] &= ~((1 << 18) | (1 << 16));

	NVIC->IP[7] |= (1 << 23); // preemptive priority set as 2; min value is 3, max and default is 0
	NVIC->ISER[0] |= (1 << 30); // interrupt enable in NVIC
}

void PORTA_IRQHandler(void)
{
	if((GPIOA->PDIR & (1 << 16)) == 0)
	{
		for (int i = 0; i < 10; i++);
		if ((GPIOA->PDIR & (1 << 17)) == 0)
		{
			if (x1 >= 255)
			{
				x1 = 255;
			}
			else
			{
				x1 += 5;
			}
		}
	}

	if((GPIOA->PDIR & (1 << 16)) == 0)
	{
		for (int i = 0; i < 10; i++);
		if ((GPIOA->PDIR & (1 << 17)) == (1 << 17))
		{
			if (x1 <= 0)
			{
				x1 = 0;
			}
			else
			{
				x1 -= 5;
			}
		}
	}

	PORTA->PCR[16] |= (1 << 24); // clear interrupt flag
}


