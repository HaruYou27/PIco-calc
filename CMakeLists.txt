cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD weact_studio_rp2040_16mb)
#set(PICO_USE_FASTEST_SUPPORTED_CLOCK 1)
# initialize pico-sdk from submodule
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PIcoCalc)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

#add_executable(test_ereader src/ssd1306_driver.cpp src/ereader.cpp src/test_ereader.cpp)
#target_link_libraries(test_ereader pico_stdlib hardware_i2c)
#pico_add_extra_outputs(test_ereader)

add_executable(test_adc src/ssd1306_driver.cpp src/sysinfo.cpp src/test_sysinfo.cpp )
target_link_libraries(test_adc pico_stdlib hardware_i2c hardware_adc)
pico_add_extra_outputs(test_adc)

# rest of your project
