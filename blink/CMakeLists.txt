add_executable(blink
        blink.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(blink pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(blink)

pico_set_program_name(blink "blink")
pico_set_program_description(blink "blink the default LED")