#include "device/door.h"

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "esp_log.h"

#include "query_string.h"
#include "connection/mqtt.h"

#define DOOR_MCPWM_UNIT             MCPWM_UNIT_1
#define DOOR_MCPWM_TIMER            MCPWM_TIMER_1
#define DOOR_MCPWM_GEN               MCPWM_OPR_A
#define DOOR_MCPWM_IO_SIGNAL        MCPWM1A

#define SERVO_MIN_PULSEWIDTH        500  // Độ rộng xung tối thiểu (micro giây) cho góc 0 độ
#define SERVO_MAX_PULSEWIDTH        2500 // Độ rộng xung tối đa (micro giây) cho góc 180 độ

uint32_t servo_per_degree_init(int degree_of_rotation) {
    return SERVO_MIN_PULSEWIDTH + (degree_of_rotation * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 180);
}

Door::Door(const char* id, gpio_num_t gpio_num) : Device(id, gpio_num) {
    // Initialize MCPWM module
    mcpwm_gpio_init(DOOR_MCPWM_UNIT, DOOR_MCPWM_IO_SIGNAL, gpio_num);
    // Configure MCPWM configuration parameters
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50 Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    
    // Set MCPWM configuration for the MCPWM unit x, timer x
    mcpwm_init(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, &pwm_config);

    sprintf(type_tring, "door");
}

void Door::setState(Device_state_t state) {
    this->state = state;

    if (state == DEVICE_STATE_ON) 
        mcpwm_set_duty_in_us(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, DOOR_MCPWM_GEN, servo_per_degree_init(90));
    else if (state == DEVICE_STATE_OFF)
        mcpwm_set_duty_in_us(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, DOOR_MCPWM_GEN, servo_per_degree_init(0));  
}