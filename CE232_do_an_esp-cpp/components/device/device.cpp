#include "device/device.h"
#include "query_string.h"
#include "connection/mqtt.h"
#include "string.h"
#include "esp_log.h"

int Device::device_count = 0;
Device* Device::device_ptrs[10];

Device::Device(const char* id, gpio_num_t gpio_num) {
    this->gpio_num = gpio_num;
    strcpy(this->id, id);
    state = DEVICE_STATE_OFF;

    device_ptrs[device_count] = this;
    device_count++;
}

void Device::printAll() {
    for(int i = 0; i < Device::device_count; i++)
        Device::device_ptrs[i]->printInfo();    
}

void Device::onMessage(char* topic, char* payload) {
    for(int i = 0; i < Device::device_count; i++)
        if(strcmp(topic, Device::device_ptrs[i]->id) == 0) {
            Device::device_ptrs[i]->eventHandler(payload);
            return;
        }
}

/*
* @brief Sau khi gọi hàm subscribeAll, nếu mqtt broker xử lí thành công yêu cần subscribe thì sẽ trả về
* esp32 một event MQTT_EVENT_SUBSCRIBED kèm subscribe_id, kiểm tra xem subscribe_id đó thuộc về device
* nào và gửi lệnh sync (đảm bảo subscribe trước khi publish).
*/
void Device::onSubscribe(int subscribe_id) {
    for(int i = 0; i < Device::device_count; i++)
        if(Device::device_ptrs[i]->subscribe_id == subscribe_id) {
            Device::device_ptrs[i]->sendSyncRequest();
            return;
        }
}

/*
* @brief subscribe to mqtt topic (device id) for all device.
*/
void Device::subscribeAll() {
    for(int i = 0; i < Device::device_count; i++)
        Device::device_ptrs[i]->subscribe();    
}

void Device::printInfo() {
    ESP_LOGI("INFO", "id: %s, type: %s, state: %d", id, type_tring, state);
}

void Device::sendACK(char* query) {
    char response[50];
    char messageID[20];

    getParameter(query, "messageID=", messageID);
    sprintf(response, "messageID=%s", messageID);

    mqtt_publish("esp32/ack", response);    
}

void Device::eventHandler(char* query) {
    sendACK(query);
    char cmd[10];
    getParameter(query, "cmd=", cmd);

    if(strcmp(cmd, "setState") == 0 || strcmp(cmd, "sync") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        setState((Device_state_t)(state[0] - '0')); // state = '0' || '1'
    }
}

void Device::sendSyncRequest() {
    char topic[50];
    char payload[50];

    sprintf(topic, "esp32/%s/sync", type_tring);
    sprintf(payload, "id=%s", id);

    int msg_id = mqtt_publish(topic, payload);
    ESP_LOGI("DEBUG", "send sync request, msg_id: %d, id: %s", msg_id, id);
}

int Device::subscribe() {
    ESP_LOGI("DEBUG", "send subscribe, id: %s, type: %s", id, type_tring);
    subscribe_id = mqtt_subscribe(id);
    return subscribe_id;
}