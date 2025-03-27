cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD weact_studio_rp2040_16mb)
#set(PICO_USE_FASTEST_SUPPORTED_CLOCK 1)
# initialize pico-sdk from submodule
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PIcoCalc)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(e_reader_test
    src/ssd1306_driver.cpp
    src/ereader.cpp
    src/ereader_test.cpp
)
target_link_libraries(e_reader_test pico_stdlib hardware_i2c)
pico_add_extra_outputs(e_reader_test)

# rest of your project
