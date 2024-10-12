#ifndef BUTTON_H
#define BUTTON_H
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define GPIO_BUTTON_INPUT GPIO_NUM_1
#define GPIO_BUTTON_OUTPUT GPIO_NUM_18

typedef enum {BUTTON_PRESSED, BUTTON_RELEASED} button_state_t;
void button_init(void);
button_state_t button_get(void);

void configuration_output(void);
void configuration_input(void);
void LED_init(void);
void LED_on(void);
void LED_off(void);
#endif