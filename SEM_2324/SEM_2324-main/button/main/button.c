#include <stdio.h>
#include "esp_log.h"
#include "button.h"

//static const char *TAG = "KKTUA"; // <- privado al módulo
 static const char *TAG = "__FILE__"; // <- prueba esto despues

/*******************************************************************/
/**
 * @brief Preparing pin corresponding to LED
 * @return none
 */
void configuration_input()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set,e.g.GPIO1
    io_conf.pin_bit_mask = 1ULL << GPIO_BUTTON_INPUT;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    gpio_set_drive_capability(GPIO_BUTTON_INPUT,GPIO_DRIVE_CAP_3);
}

void configuration_output()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = 1ULL << GPIO_BUTTON_OUTPUT;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    gpio_set_drive_capability(GPIO_BUTTON_OUTPUT,GPIO_DRIVE_CAP_3);
}

void button_init(void)
{
    ESP_LOGI(TAG,"Called button_init()\n");
    configuration_input();
}
button_state_t button_get(void) 
{
    uint8_t pin_level;
    pin_level = gpio_get_level(GPIO_BUTTON_INPUT);
    if(pin_level == 0)
    {
        return BUTTON_PRESSED;
    }
    else
    {
        return BUTTON_RELEASED;
    }
}

void LED_init(void) 
{
    ESP_LOGI(TAG,"Called LED_init()\n");
    //printf("Called LED_init()\n");
    configuration_output();
}
void LED_on(void)
{
    ESP_LOGI(TAG,"Called LED_on()\n");
    gpio_set_level(GPIO_BUTTON_OUTPUT,1);
}
void LED_off(void) {
    ESP_LOGI(TAG,"Called LED_off()\n");
    gpio_set_level(GPIO_BUTTON_OUTPUT,0);
}