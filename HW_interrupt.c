/*
 * HW_interrupt.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "HW_interrupt.h"


void PORTD_IRQHandler(void)
{
	GPIOD->PTOR |= (1 << 1);
	PORTD->PCR[4] |= (1 << 24); // clear interrupt flag
}

void HW_interrupt_init(void)
{
   PORTD->PCR[1] |= (1 << 8);  // PORTD pin 1 in alt mode

   GPIOD->PDDR |= (1 << 1);  // PORTD pin 1 set as output

   GPIOD->PDOR |= (1 << 1); // PORTD pin 1 default low

   GPIOD->PDDR |= (0 << 4);  // PORTD pin 4 set as input

   PORTD->PCR[4] = (1 << 8) | (0 << 1) | (0 << 0); // PORTD pin 4 in alt1 mode, pull down enable

   PORTD->PCR[4] |= (1 << 19) | (1 << 17) | (1 << 16);  // interrupt configuration on PORTD pin 4

   NVIC->IP[7] |= (1 << 32) | (1 << 31); // preemptive priority set as 3; min value is 3, max and default is 0

   NVIC->ISER[0] |= (1 << 31); // interrupt enable in NVIC
}
