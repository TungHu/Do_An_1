#include <stdio.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "connection/mqtt.h"
#include "connection/wifi.h"

#include "device/device.h"
#include "device/led.h"
#include "device/fan.h"
#include "device/door.h"
#include "built_in_led/led.h"

#define LED_ID              "6649a8168950f2c97e5cc8cd"
#define LED_GPIO            GPIO_NUM_5
#define FAN_ID              "6612c435e056da36ad2126a2"
#define FAN_GPIO            GPIO_NUM_18
#define DOOR_ID             "66814ce91a33844ee9820553"
#define DOOR_GPIO           GPIO_NUM_25


//Led led(LED_ID, LED_GPIO);

extern "C" void app_main(void) {
  //Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }

  built_in_led_init();
  built_in_led_set_state(LED_BLINK);

  //new Led(LED_ID, LED_GPIO);
  new Door(DOOR_ID, DOOR_GPIO);
  //new Fan(FAN_ID, FAN_GPIO);
  Device::printAll();

  wifi_init_sta();
  mqtt_app_start();    
}