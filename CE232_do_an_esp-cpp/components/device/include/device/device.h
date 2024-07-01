#ifndef __DEVICE_H__
#define __DEVICE_H__

#define DEVICE_ID_SIZE 24 + 1

#include "driver/gpio.h"

typedef enum {
    DEVICE_STATE_OFF = (char)0,
    DEVICE_STATE_ON,
} Device_state_t;

class Device;

class Device {
public:
    char id[DEVICE_ID_SIZE];
    Device_state_t state;
    char type_tring[10];
    gpio_num_t gpio_num;
    int subscribe_id;
    Device(const char* id, gpio_num_t gpio_num);
    virtual void setState(Device_state_t state) = 0;
    virtual void eventHandler(char* query);
    virtual void printInfo();
    void sendACK(char* query);
    void sendSyncRequest();
    int subscribe();
    /* --------------- STATIC --------------- */
    static int device_count;
    static Device* device_ptrs[10];
    static void printAll();
    static void onMessage(char* topic, char* payload);
    static void onSubscribe(int subscribe_id);
    static void subscribeAll();
};

#endif