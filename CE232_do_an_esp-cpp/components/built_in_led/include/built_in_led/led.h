#ifndef __BUILT_IN_LED_H__
#define __BUILT_IN_LED_H__

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LED_PIN             GPIO_NUM_2

typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_BLINK, 
} LedState_t;

void built_in_led_init();
void built_in_led_set_state(LedState_t state);

#endif