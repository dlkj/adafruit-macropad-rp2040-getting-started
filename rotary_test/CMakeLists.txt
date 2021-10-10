add_executable(rotary_test
        rotary_test.c
        )

# Double tap reset into bootrom is injected by linking with the
# pico_bootsel_via_double_reset library
target_link_libraries(rotary_test
        pico_stdlib
        hardware_spi
        pico_bootsel_via_double_reset
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(rotary_test 1)
pico_enable_stdio_uart(rotary_test 0)

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(rotary_test PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
)

# create map/bin/hex file etc.
pico_add_extra_outputs(rotary_test)