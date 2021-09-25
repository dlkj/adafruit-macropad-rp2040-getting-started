#include <stdio.h>
#include "pico/stdlib.h"

//View in ubuntu:
//sudo minicom -b 115200 -o -D /dev/ttyACM[0-9]

int main() {
    stdio_init_all();
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
    return 0;
}