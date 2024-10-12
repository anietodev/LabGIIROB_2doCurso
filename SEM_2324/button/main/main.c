#include <stdio.h>
#include "button.h"


void delay(uint16_t retardo);

void app_main(void)
{
    printf("Hola, LED\n\r");
    LED_init();
    button_init();
    button_state_t bt;
    for(;;)
    {
        bt = button_get();
        if(bt == BUTTON_PRESSED) 
        {
            LED_on();
        }
        else
        {
            LED_off();
        }  
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