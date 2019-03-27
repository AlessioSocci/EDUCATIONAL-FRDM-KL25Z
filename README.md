Educational BARE-METAL Project

Test some basic funcitonality for NXP KL25 in FRDM board, without libraries.

ATTENTION!! There are many inconsistencies with KL25Z data sheet when try to set preemptive priority !! ...this code seems to work well !!


-    GPIO IN / HW Interrupt: toggle blue led in ISR, set low preemptive priority. 

-    LPTMR: toggle red led in ISR, set preemptive priority of ISR;
    
-    PIT: pit trigger ISR every 1s, service routine increment a variable for delay function, set high preemptive priority of ISR to allow                                       the usage of delay function into other ISR.

-    ADC: 16 bit read from external potentiometer, in polling mode;

-    DAC: put in external pin ADC read value, truncated in 12 bit;

-    PWM: configure TPM for put in external pin a pwm signal;

-    UART: set serial communication at 115200 br to ESP8266 -01, Wi-Fi SoC module; 

-    I2C: set sincronous serial to IR Thermometer Melexis MLX90614. (... but it does not work yet...)

-    MAIN: just once, send string to client from ESP-01 in mode AP, adc read and dac out in task 1, try to read MLX90614 in task 2;



