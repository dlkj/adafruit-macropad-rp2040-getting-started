add_executable(neopixel_test
        neopixel_test.c
        )

# generate the header file into the source tree
pico_generate_pio_header(neopixel_test ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Double tap reset into bootrom is injected by linking with the
# pico_bootsel_via_double_reset library
target_link_libraries(neopixel_test
        PRIVATE
        pico_stdlib
        hardware_pio
        pico_bootsel_via_double_reset
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(neopixel_test 1)
pico_enable_stdio_uart(neopixel_test 0)

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(neopixel_test PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
)

# create map/bin/hex file etc.
pico_add_extra_outputs(neopixel_test)