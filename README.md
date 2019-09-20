Soft Real Time O.S. with Non-Preemptive First Come First Served Task Scheduling, Preemptive Prioritized Interrupt, "Educational" Project - NXP ARM Cortex M0+

Test some basic functionality for NXP KL25 in FRDM board, without libraries.

ATTENTION!! There are many inconsistencies with KL25Z data sheet when try to set preemptive priority !! ...this code seems to work well !!


-    GPIO IN / HW Interrupt: toggle blue led in ISR, set low preemptive priority. 

-    LPTMR: toggle red led in ISR, set preemptive priority of ISR;
    
-    PIT: pit trigger ISR every 1s, service routine increment a variable for delay function, set high preemptive priority of ISR to allow                                                            delay function into other ISR.

-    ADC: 16 bit read from external potentiometer, in polling mode;

-    DAC: put in external pin ADC readed value, truncated in 12 bit;

-    PWM: configure TPM for put in external pin a pwm signal;

-    UART0: set serial communication at 115200 br to ESP8266 -01, Wi-Fi SoC module; 

-    I2C: set sincronous serial to IR Thermometer Melexis MLX90614. 

-    UART2: implement DMX 512 protocol in RS 485 physical layer using max 485 device.

-    HW triggered ISR: rotary incremental encoder managing;

-    SPI: communication with driver SH1106 in 132x64 OLED display.

-    MAIN: just once, send string to client from ESP-01 in mode AP and draw some pixel into OLED display
_ blink green led in task 0;
_ adc read and dac out, MLX90614 T ambient in task 1;
_ read MLX90614 T object in task 2; 
_ encoder "data-change" acquisition to set dmx frame 3-4-5, respectively to dim red-green-blue leds, frame index selected by push  button, managed by HW interrupt, refresh WiFi sen array with encoder parameters, in task 3; 
_ DMX 512 with 129 frame to "PAR LED" 5 dmx channel Lighting device, in task 4. 
_ send DMX channel 3-4-5 value to WiFi, in task 5. (...there are a problems to solve with time duration of this routine...)

Every task are triggered by counter incremented in PIT interrupt service routine.



