idf_component_register (
    SRCS "device.cpp" "door.cpp" "fan.cpp" "led.cpp"
    INCLUDE_DIRS "include"
    REQUIRES mqtt driver connection query_string
)