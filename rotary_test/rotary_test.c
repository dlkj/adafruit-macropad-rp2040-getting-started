
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"

static void init_pins(){

    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_LED_PIN, "On-board red LED"));
    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_BUTTON_PIN, "Rotary encoder button"));

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

}

int32_t rot_idx = 0;
int8_t rot_qrt_idx = 0;

uint8_t rot_state = 0x3;

void gpio_callback(uint gpio, uint32_t events) {

    uint8_t new_state = (uint8_t)((gpio_get_all() >> 17) & 0x3);

    //printf("p:%" PRIu8 " r:%d q:%" PRIi8 "\n", new_state, rot_idx, rot_qrt_idx);

    if(rot_state == new_state){
        //printf("~0\n");
        return; //no change, shouldn't really happen
    }

    static const int8_t grey_table[16] = {
        0,
        -1,
        +1,
        0,
        +1,
        0,
        0,
        -1,
        -1,
        0,
        0,
        +1,
        0,
        +1,
        -1,
        0,
    };


    int8_t grey = grey_table[(rot_state ) | (new_state << 2)];

    rot_state = new_state;

    rot_qrt_idx += grey;


    if(rot_qrt_idx > 3){
        rot_idx++;
        rot_qrt_idx = 0;
        //printf("%d up\n", rot_idx);
    }
    else if(rot_qrt_idx < -3){
        rot_idx--;
        rot_qrt_idx = 0;
        //printf("%d down\n", rot_idx);
    }

}

int main() {

    bi_decl(bi_program_name("rotary test"));
    bi_decl(bi_program_description("test reading the rotary encoder on the macropad board"));

    init_pins();

    stdio_init_all();

    gpio_set_irq_enabled_with_callback(ADAFRUIT_MACROPAD_ROTA_PIN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled(ADAFRUIT_MACROPAD_ROTB_PIN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);

    int32_t last_rot = rot_idx;
    while (true) {

        if(rot_idx != last_rot) {
            printf("idx: %d\n", rot_idx);
            last_rot = rot_idx;
        }
        sleep_ms(10);
    }
}