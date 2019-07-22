/*
 * HW_interrupt.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "HW_interrupt.h"

uint8_t y = 3;

void PORTD_IRQHandler(void)
{
	uint32_t timeOut = ticks + 300; // anti-ripple
	while ((timeOut > ticks) & ((GPIOD->PDIR & (1 << 1)) == (1 << 1) )) // change DMX frame, frame correspond at DMX channel, for PAR LED RGB device, frame 1(master dimmer),2,3 (red),4(green),5(blue) are significant.
	{
		y++; //

		if(y > 5)
		{
			y = 3;
		}

		PORTD->PCR[4] |= (1 << 24); // clear interrupt flag
	}
	PORTD->PCR[4] |= (1 << 24); // clear interrupt flag
}

void HW_interrupt_init(void)
{
   PORTD->PCR[1] |= (1 << 8)  | (1 << 4); // PORTD pin 1 in alt mode, passive filter on

   GPIOD->PDDR |= (1 << 1); // PORTD pin 1 set as output

   GPIOD->PDOR |= (1 << 1); // PORTD pin 1 default low

   GPIOD->PDDR &= ~(1 << 4); // PORTD pin 4 set as input

   PORTD->PCR[4] = (1 << 8) | (0 << 1) | (0 << 0); // PORTD pin 4 in alt1 mode, pull down enable

   PORTD->PCR[4] |= (1 << 19) | (1 << 16); // interrupt configuration on PORTD pin 4, on rising edge

   NVIC->IP[7] |= (1 << 31) | (1 << 30); // preemptive priority set as 3; min value is 3, max and default is 0

   NVIC->ISER[0] |= (1 << 31); // interrupt disable in NVIC
}
