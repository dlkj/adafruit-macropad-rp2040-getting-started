add_executable(board_test
        board_test.c
        )

# Double tap reset into bootrom is injected by linking with the
# pico_bootsel_via_double_reset library
target_link_libraries(board_test
        pico_stdlib
        pico_bootsel_via_double_reset
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(board_test 1)
pico_enable_stdio_uart(board_test 0)

target_link_libraries(board_test
        pico_stdlib
        pico_bootsel_via_double_reset
        )

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(board_test PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
)

# create map/bin/hex file etc.
pico_add_extra_outputs(board_test)