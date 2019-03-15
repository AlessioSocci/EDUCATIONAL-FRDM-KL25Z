/*
 * time.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */
#include "time.h"


uint32_t ticks = 0;

void PIT_IRQHandler(void)
{
	ticks++;
	PIT_CH->TFLAG = (1 << 0);
}

void pit_init(void)
{
   /* PORTB pin 19 in alt1 mode */
   PORTB->PCR[19] |= (1 << 8);

   /* PORTB pin 19 set as output */
   GPIOB->PDDR |= (1 << 19);

   /* PORTB pin 19 default low */
   GPIOB->PDOR |= (1 << 19);

   /* enable clock for PIT */
   SIM->SCGC6 |= (1 << 23);

   /* enable PIT module */
   PIT->MCR |= (0 << 30);

   /* set time period */
   PIT_CH->LDVAL = CLOCK_GetBusClkFreq()/1000;

   /* enable timer interrupt */
   PIT_CH->TCTRL |= (1 << 1) | (1 << 0);

   /* interrupt enable in NVIC */
   NVIC->ISER[0] |= NVIC->ISER[0] | (1 << 22);

   /* set priority */
  // NVIC->IP[5] = NVIC->IP[5] | (1 << 22);
}

void delay (uint16_t mseconds) // Delay function, based on pit
{
    uint32_t currTicks = ticks;

    while ((ticks - currTicks) < mseconds);
}
