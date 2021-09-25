
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/unique_id.h"

int main() {

    bi_decl(bi_program_name("board test"));
    bi_decl(bi_program_description("test all the hardware functions of the macropad board"));

    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_LED_PIN, "On-board red LED"));
    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_BUTTON_PIN, "Rotary encoder button"));

    stdio_init_all();

    gpio_init(ADAFRUIT_MACROPAD_LED_PIN);

    gpio_init(ADAFRUIT_MACROPAD_BUTTON_PIN);
    gpio_init(ADAFRUIT_MACROPAD_ROTA_PIN);
    gpio_init(ADAFRUIT_MACROPAD_ROTB_PIN);

    gpio_init(ADAFRUIT_MACROPAD_KEY1_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY2_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY3_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY4_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY5_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY6_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY7_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY8_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY9_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY10_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY11_PIN);
    gpio_init(ADAFRUIT_MACROPAD_KEY12_PIN);


    gpio_set_dir(ADAFRUIT_MACROPAD_LED_PIN, GPIO_OUT);

    gpio_set_dir(ADAFRUIT_MACROPAD_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_ROTA_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_ROTB_PIN, GPIO_IN);

    gpio_set_dir(ADAFRUIT_MACROPAD_KEY1_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY2_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY3_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY4_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY5_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY6_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY7_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY8_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY9_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY10_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY11_PIN, GPIO_IN);
    gpio_set_dir(ADAFRUIT_MACROPAD_KEY12_PIN, GPIO_IN);

    gpio_pull_up(ADAFRUIT_MACROPAD_BUTTON_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_ROTA_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_ROTB_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY1_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY2_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY3_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY4_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY5_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY6_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY7_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY8_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY9_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY10_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY11_PIN);
    gpio_pull_up(ADAFRUIT_MACROPAD_KEY12_PIN);

    //wait for the usb serial port to init on the host
    sleep_ms(1000);

    pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

    printf("\nBoard unique identifier:");
    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++i) {
        printf(" %02x", board_id.id[i]);
    }
    printf("\n");

    //bool last_button = false;
    while (1) {
        // bool button = gpio_get(ADAFRUIT_MACROPAD_BUTTON_PIN);
        // gpio_put(ADAFRUIT_MACROPAD_LED_PIN, !button);
        // if(!button && last_button){
        //     printf(".");
        // }
        // last_button = button;

        printf("%x\n", gpio_get_all());
        sleep_ms(100);
    }
}