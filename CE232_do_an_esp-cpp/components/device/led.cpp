#include "device/led.h"

#include "string.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "query_string.h"
#include "connection/mqtt.h"

void Led::setState(Device_state_t state) {
    this->state = state;
    gpio_set_level(gpio_num, state);    
}

Led::Led(const char* id, gpio_num_t gpio_num) : Device(id, gpio_num) {
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
    sprintf(type_tring, "led");
}