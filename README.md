Educational BARE-METAL Project

Test some basic funcitonality for NXP KL25 in FRDM board, without libraries.

    GPIO IN / HW Interrupt: enter ISR, turn on blue led, wait some ms, turn of led, clear flag, exit ISR;

    LPTMR: toggle red led in ISR;
    
    PIT: pit trigger ISR every 1s, service routine increment a variable for delay function.
    
    ADC: 16 bit read from external potentiometer, in polling mode;

    DAC: put in external pin ADC read value, truncated in 12 bit;

    PWM: configure TPM for put in external pin a pwm signal;

    UART: set serial communication at 115200 br to ESP8266 -01, Wi-Fi module;
    
    MAIN: adc read, dac out, send AT test command to ESP-01.
