#include <stdio.h>
#include "esp_log.h"
#include "led.h"

//static const char *TAG = "KKTUA"; // <- privado al módulo
 static const char *TAG = "__FILE__"; // <- prueba esto despues

/*******************************************************************/
/**
 * @brief Preparing pin corresponding to LED
 * @return none
 */


void LED_init(void) 
{
    ESP_LOGI(TAG,"Called LED_init()\n");
    //printf("Called LED_init()\n");
}
void LED_on(void)
{
    ESP_LOGI(TAG,"Called LED_on()\n");
    //printf("Called LED_on()\n");
}
void LED_off(void) {
    ESP_LOGI(TAG,"Called LED_off()\n");
    //printf("Called LED_off()\n");
}