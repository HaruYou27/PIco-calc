cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD weact_studio_rp2040_16mb)
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(display)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${CMAKE_PROJECT_NAME}
    test.cpp
    ssd1306_driver.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib hardware_i2c)

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
# rest of your project
