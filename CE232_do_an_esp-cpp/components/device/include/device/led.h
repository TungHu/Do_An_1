#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include "device.h"

class Led : public Device {
public:
    virtual void setState(Device_state_t state);
    Led(const char* id, gpio_num_t gpio_num);
};

#endif