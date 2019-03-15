/*
 * adc.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#ifndef ADC_C_
#define ADC_C_

#include "adc.h"


void adc_init(void)
{
	// ADC

    SIM->SCGC6 = SIM->SCGC6 | (1 << 27); // enable clock for ADC0

    PORTB->PCR[1] = 0;  // PORTB pin1 as ADC default mode

    ADC0->CFG1 =  ADC0->CFG1 | (1 << 5) | (1 << 3) | (1 << 2); // set freq. of sampling by bus divide (2 in this case), quantization bit is 16

    ADC0->SC3 = 0; /* ADC0 SC3 */
}

uint16_t adc_read (void)
{
	uint16_t dataADC = 0;
	/* on configuration channel, ch 9 in this case, conversion start */
	ADC0->SC1[0] = (1 << 3) | (1 << 0);

	/* Check for conversion is complete or not*/
	while((ADC0->SC1[0] & (1<<7)) == 0)
	{

	}

	dataADC = ADC0->R[0];
	dataADC = (dataADC * 3300) / 65535;
	return dataADC;
}

#endif /* ADC_C_ */
