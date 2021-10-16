add_executable(audio_test
        audio_test.c
        )

# Double tap reset into bootrom is injected by linking with the
# pico_bootsel_via_double_reset library
target_link_libraries(audio_test
        pico_stdlib
        pico_bootsel_via_double_reset
        pico_audio_pwm
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(audio_test 1)
pico_enable_stdio_uart(audio_test 0)

# Specify a GPIO to be used as a bootloader activity LED:
target_compile_definitions(audio_test PRIVATE
        PICO_BOOTSEL_VIA_DOUBLE_RESET_ACTIVITY_LED=13
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(audio_test)

target_compile_definitions(audio_test PRIVATE
        #define for our example code
        USE_AUDIO_PWM=1
        )
