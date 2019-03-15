/*
 * pwm.c
 *
 *  Created on: 15 mar 2019
 *      Author: Alessio
 */

#include "pwm.h"


void pwm_init(void)
{
    SIM->SCGC6 |= (1 << 24);  // enable timer on TPM0

    SIM->SOPT2 |= (1 << 25); // TPM0 clock source

    TPM0->SC |= (1 << 5) | (1 << 3) | (1 << 1); // TPM0 clock mode select, prescaler factor set as 8

    SIM->SCGC5 = SIM->SCGC5 | (1 << 9); // PORTA clock enable

    PORTA->PCR[4] = (1 << 9) | (1 << 8); // PORTA pin 4 in alt 4 mode

    TPM0->CONTROLS[1].CnSC = TPM0->CONTROLS[1].CnSC | (1 << 5) | (1 << 3); // PORTA pin 4 is on channel 1 of TPMO, so set it...

    TPM0->CONTROLS[1].CnV =  (1 << 14); // set duty
}
