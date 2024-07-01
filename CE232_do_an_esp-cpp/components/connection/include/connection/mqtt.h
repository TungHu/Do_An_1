#ifndef __MQTT_H__
#define __MQTT_H__

/* MQTT (over TCP) Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_event.h"

void log_error_if_nonzero(const char *message, int error_code);

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

void mqtt_app_start(void);

/*
 * @brief Use this function to send a mqtt message
 * @param topic mqtt topic
 * @param data_string payload as null terminated string
*/
int mqtt_publish(char* topic, char* data_string);

int mqtt_subscribe(char* topic);

#ifdef __cplusplus
}
#endif

#endif