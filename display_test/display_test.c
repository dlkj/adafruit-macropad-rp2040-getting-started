
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"



static void write_command(uint8_t command) {
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 0);
    asm volatile("nop \n nop \n nop");
    spi_write_blocking(spi1, &command, 1);
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

static void write_command_arg(uint8_t command, uint8_t arg) {
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 0);
    asm volatile("nop \n nop \n nop");
    uint8_t buf [2];
    buf[0] = command;
    buf[1] =  arg;

    spi_write_blocking(spi1, buf, 2);
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

static void write_data(uint8_t data) {
    spi_write_blocking(spi1, &data, 1);
}


int main() {

    bi_decl(bi_program_name("display test"));
    bi_decl(bi_program_description("test driving the oled display on the macropad board"));

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

    //init SPI0 @ 10MHz
    spi_init(spi1, 10 * 1000 * 1000);
    gpio_set_function(ADAFRUIT_MACROPAD_DISPLAY_MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ADAFRUIT_MACROPAD_DISPLAY_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ADAFRUIT_MACROPAD_DISPLAY_MOSI_PIN, GPIO_FUNC_SPI);

    bi_decl(bi_3pins_with_func(ADAFRUIT_MACROPAD_DISPLAY_MISO_PIN, ADAFRUIT_MACROPAD_DISPLAY_MOSI_PIN, ADAFRUIT_MACROPAD_DISPLAY_SCK_PIN, GPIO_FUNC_SPI));

    //Init chip sellect and drive low (active low)
    gpio_init(ADAFRUIT_MACROPAD_DISPLAY_OLED_CS_PIN);
    gpio_set_dir(ADAFRUIT_MACROPAD_DISPLAY_OLED_CS_PIN, GPIO_OUT);
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_CS_PIN, 0);
    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_DISPLAY_OLED_CS_PIN, "OLED_CS"));

    //Init display reset - drive high (active low)
    gpio_init(ADAFRUIT_MACROPAD_DISPLAY_OLED_RESET_PIN);
    gpio_set_dir(ADAFRUIT_MACROPAD_DISPLAY_OLED_RESET_PIN, GPIO_OUT);
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_RESET_PIN, 1);
    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_DISPLAY_OLED_RESET_PIN, "OLED_RESET"))

    //Init Data/Command - init to command
    gpio_init(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN);
    gpio_set_dir(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, GPIO_OUT);
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 0);
    bi_decl(bi_1pin_with_name(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, "OLED_DC"))

    for(int j = 0; j < 8; j++){
        write_command(0xB0 | j);
        write_command(0x02);
        write_command(0x10);


        for(int i = 0; i < 16*8; i++){
            write_data(0);
        }
    }

    write_command(0xAF); //display on

    sleep_ms(100);
 
    while(true){

        for(int j = 0; j < 8; j++){
            write_command(0xB0 | j);
            write_command(0x02);
            write_command(0x10);


            for(int i = 0; i < 16*8; i++){
                write_data(0);
            }
        }

        for(int j = 0; j < 8; j++){
            write_command(0xB0 | j);
            write_command(0x02);
            write_command(0x10);


            for(int i = 0; i < 16*8; i++){
                write_data((~gpio_get_all()) & 0xff);
                sleep_ms(10);
            }
        }
    }
}