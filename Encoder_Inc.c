/*
 * Encoder_Inc.c
 *
 *  Created on: 20 lug 2019
 *      Author: Alessio
 */

#include "Encoder_Inc.h"
#include "time.h"
#include "HW_interrupt.h"

uint8_t encoderOut[129];

void encoder_init(void)
{
	for (int i = 0; i < 129; i++)
	{
		encoderOut[i] = 0;
	}

	PORTA->PCR[16] |= (1 << 8) | (1 << 4); // Set Alt 1 mode for GPIO, passive filter on
	PORTA->PCR[17] |= (1 << 8) | (1 << 4); // Set Alt 1 mode for GPIO, passive filter on

	GPIOA->PDDR &= ~(1 << 16);  // PORTD pin 6 set as input
	GPIOA->PDDR &= ~(1 << 17);  // PORTD pin 7 set as input

	PORTA->PCR[16] |= (1 << 19) | (1 << 17);  // interrupt configuration on PORTA pin 16, on falling edge
	PORTA->PCR[16] &= ~((1 << 18) | (1 << 16));

	NVIC->IP[7] |= (1 << 23); // preemptive priority set as 2; min value is 3, max and default is 0
	NVIC->ISER[0] |= (1 << 30); // interrupt enable in NVIC
}

void PORTA_IRQHandler(void)
{
	if((GPIOA->PDIR & (1 << 16)) != (1 << 16))
	{
		uint32_t timeOut = ticks + 5;
		while (timeOut > ticks)
		{
			if (((GPIOA->PDIR & (1 << 17)) == (1 << 17)))
			{
				if(encoderOut[y] >= 250)
				{
					encoderOut[y] = 255;
				}
				else
				{
					encoderOut[y] += 10;
				}

				NVIC->ICPR[0] = (1 << 30);
				PORTA->PCR[16] |= (1 << 24); // clear interrupt flag

				return;
			}
		}
	}

	if((GPIOA->PDIR & (1 << 16)) != (1 << 16))
	{
		uint32_t timeOut = ticks + 5;
		while (timeOut > ticks)
		{
			if (((GPIOA->PDIR & (1 << 17)) != (1 << 17)))
			{
				if(encoderOut[y] <= 5)
				{
					encoderOut[y] = 0;
				}
				else
				{
					encoderOut[y] -= 10;
				}

				NVIC->ICPR[0] = (1 << 30);
				PORTA->PCR[16] |= (1 << 24); // clear interrupt flag

				return;
			}
		}
	}

	PORTA->PCR[16] |= (1 << 24); // clear interrupt flag
}


