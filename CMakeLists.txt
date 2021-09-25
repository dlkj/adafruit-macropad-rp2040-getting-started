cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(adafruit-macropad-rp2040-getting-started C CXX ASM)

set(PICO_BOARD adafruit_macropad_rp2040)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        )

# project subdirectories
add_subdirectory(blink)
add_subdirectory(hello_usb)
add_subdirectory(board_test)