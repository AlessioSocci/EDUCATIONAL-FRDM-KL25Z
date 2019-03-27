/*
 * time.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */
#include "time.h"


uint32_t ticks = 0;
uint16_t task1 = 0;
uint16_t task2 = 0;
uint16_t time1 = 10000; // threshold of counter in ms
uint16_t time2 = 1000; // threshold of counter in ms

uint8_t task1Flag = 0;
uint8_t task2Flag = 0;


void task1_incrementCounter(void)
{
   	task1++;
	if (task1 == time1)
	{
		task1 = 0;
		task1Flag = 1;
	}
}
void task2_incrementCounter(void)
{
   	task2++;
	if (task2 == time2)
	{
		task2 = 0;
		task2Flag = 1;
	}
}

void PIT_IRQHandler(void)
{
	ticks++;
	task1_incrementCounter();
	task2_incrementCounter();
	GPIOB->PTOR |= (1 << 19);
	PIT->CHANNEL->TFLG = (1 << 0); // Clear interrupt flag
}

void delay(uint16_t mseconds) // Delay function, based on pit
{
    uint32_t currTicks = ticks;

    while((ticks - currTicks) < mseconds);
}

void pit_init(void)
{
   PORTB->PCR[19] |= (1 << 8); // PORTB pin 19 in alt1 mode, green led

   GPIOB->PDDR |= (1 << 19); // PORTB pin 19 set as output

   GPIOB->PDOR |= (1 << 19); // PORTB pin 19 default low

   SIM->SCGC6 |= (1 << 23);  // enable clock for PIT

   PIT->MCR &= ~(1 << 1); // enable PIT module // Attention!! There are many error in reference manual regarding bit field.

   PIT->CHANNEL->LDVAL |= (CLOCK_GetBusClkFreq() / 1000) - 1; // set time period : desired timing * bus clock -1

   PIT->CHANNEL->TCTRL |= (1 << 1) | (1 << 0); // Timer interrupt enable, Timer enable

   NVIC->IP[5] |= (1 << 22); // preemptive priority 1, min value is 3, max and default is 0

   NVIC->ISER[0] |= (1 << 22);  // interrupt enable in NVIC

}
