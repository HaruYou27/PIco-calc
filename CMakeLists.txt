cmake_minimum_required(VERSION 3.13...3.27)

# initialize pico-sdk from submodule
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PIcoCalc)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(pico-vfs)
pico_enable_filesystem(${CMAKE_PROJECT_NAME})

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp 
)

target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib hardware_i2c)

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

# rest of your project
