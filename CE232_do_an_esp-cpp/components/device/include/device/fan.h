#ifndef __FAN_H__
#define __FAN_H__

#include <stdint.h>
#include "device/device.h"

typedef enum {
    FAN_LEVEL_LOW = 0,
    FAN_LEVEL_NORMAL = 1,
    FAN_LEVEL_HIGH = 2,
} Fan_level_t;

class Fan : public Device {
protected:
    Fan_level_t level;
public:
    Fan(const char* id, gpio_num_t gpio_num);
    virtual void setState(Device_state_t state);
    virtual void eventHandler(char* query);
    virtual void printInfo();
    void setLevel(Fan_level_t level);
    void operate();
};

#endif