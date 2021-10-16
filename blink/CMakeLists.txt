add_executable(blink
        blink.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(blink
        pico_stdlib
        pico_bootsel_via_double_reset
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(blink PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)