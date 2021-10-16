add_executable(usb_keyboard_test
        main.c
        usb_descriptors.c
)

# Double tap reset into bootrom is injected by linking with the
# pico_bootsel_via_double_reset library
target_link_libraries(usb_keyboard_test
        pico_stdlib
        pico_bootsel_via_double_reset
        tinyusb_device
        tinyusb_board
)

# Can't use pico_enable_stdio_usb with tinyusb 

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(usb_keyboard_test PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
)

target_include_directories(usb_keyboard_test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# create map/bin/hex file etc.
pico_add_extra_outputs(usb_keyboard_test)