#include "device/fan.h"

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "esp_log.h"

#include "query_string.h"
#include "connection/mqtt.h"

#define FAN_MCPWM_UNIT              MCPWM_UNIT_0
#define FAN_MCPWM_TIMER             MCPWM_TIMER_0
#define FAN_MCPWM_GEN               MCPWM_OPR_A
#define FAN_MCPWM_IO_SIGNAL         MCPWM0A

Fan::Fan(const char* id, gpio_num_t gpio_num) : Device(id, gpio_num) {
    //Initialize MCPWM
    mcpwm_gpio_init(FAN_MCPWM_UNIT, FAN_MCPWM_IO_SIGNAL, gpio_num);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, &pwm_config);

    level = FAN_LEVEL_LOW;
    sprintf(type_tring, "fan");
}

void Fan::setState(Device_state_t state) {
    this->state = state;
    operate();
}

void Fan::setLevel(Fan_level_t level) {
    this->level = level;
    operate();
}

void Fan::operate() {
    float duty = 0; // default duty for off state.
    if(state == DEVICE_STATE_ON)
        switch(level) {
            case FAN_LEVEL_LOW:     duty = 45; break;
            case FAN_LEVEL_NORMAL:  duty = 60; break;
            case FAN_LEVEL_HIGH:    duty = 100; break;
            default:                duty = 0; break;
        }

    mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, duty);
}

void Fan::eventHandler(char* query) {
    sendACK(query);
    char cmd[10];
    getParameter(query, "cmd=", cmd);

    if(strcmp(cmd, "setState") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        setState((Device_state_t)(state[0] - '0')); // state = '0' || '1'
    } else if(strcmp(cmd, "setLevel") == 0) {
        char level[10];
        getParameter(query, "level=", level);
        setLevel((Fan_level_t)(level[0] - '0')); // level = '0' | '1' | '2'
    } else if(strcmp(cmd, "sync") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        setState((Device_state_t)(state[0] - '0')); // state = '0' || '1'

        char level[10];
        getParameter(query, "level=", level);
        setLevel((Fan_level_t)(level[0] - '0')); // level = '0' | '1' | '2'       
    }
}

void Fan::printInfo() {
    ESP_LOGI("INFO", "id: %s, type: %s, state: %d, level: %d", id, type_tring, state, level);
}