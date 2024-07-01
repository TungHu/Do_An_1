#ifndef __DOOR_H__
#define __DOOR_H__

#include "device/device.h"

class Door : public Device {
public:
    virtual void setState(Device_state_t state);
    Door(const char* id, gpio_num_t gpio_num);
};

#endif