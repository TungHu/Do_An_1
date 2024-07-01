idf_component_register (
    SRCS "wifi.cpp" "mqtt.cpp"
    INCLUDE_DIRS "include"
    REQUIRES mqtt esp_wifi nvs_flash device built_in_led
)