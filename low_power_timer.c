/*
 * low_power_timer.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */
#include "low_power_timer.h"


void LPTMR0_IRQHandler(void)
{
	GPIOB->PTOR |= (1 << 18);
	LPTMR0->CSR |= (1 << 7);
}

void LPTMR0_init(void)
{
	// LPTMR
	SIM->SCGC5 |= (1 << 0); // LPT access enable

	PORTB->PCR[18] |= (1 << 8); // PORTB pin 18 in alt1 mode

	GPIOB->PDDR |= (1 << 18); // PORTB pin 18 set as output

	GPIOB->PDOR |= (1 << 18); // PORTB pin 18 default low */

	LPTMR0->PSR |= (1 << 2) | (1 << 0); // Prescaler clock enable and bypass division

	LPTMR0->CMR |= 2000; // Set compare value

	LPTMR0->CSR |= (1 << 0) | (1 << 6); // timer enable and timer interrupt enable ( CNR counter value is reset when TCF timer compare flag is set, TCF is set when CNR is equal to CMR)

    NVIC->ISER[0] |= (1 << 28); // interrupt enable in NVIC
}
