#include <stdio.h>
#include "led.h"

void delay(uint16_t retardo);

void app_main(void)
{
    for(;;)
    {
        LED_init();
        delay(50);
        LED_on();
        delay(50);
        LED_off();
        delay(50);
    }
}
void delay(uint16_t retardo)
{
    while(retardo--) 
    {
        for(volatile uint32_t i = 0; i < 100000UL; i++) {};
    }
}