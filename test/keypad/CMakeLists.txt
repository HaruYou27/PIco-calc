cmake_minimum_required(VERSION 3.13...3.27)

# initialize pico-sdk from submodule
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(keypad)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(keypad
    keypad.c
)

target_link_libraries(keypad pico_stdlib)

# rest of your project
