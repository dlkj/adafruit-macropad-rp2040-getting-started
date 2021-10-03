
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

static void write_command(uint8_t command) {
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 0);
    asm volatile("nop \n nop \n nop");
    spi_write_blocking(spi_default, &command, 1);
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

    spi_write_blocking(spi_default, buf, 2);
    asm volatile("nop \n nop \n nop");
    gpio_put(ADAFRUIT_MACROPAD_DISPLAY_OLED_DC_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

static void write_data(uint8_t data) {
    spi_write_blocking(spi_default, &data, 1);
}

static void init_display(){

    write_command(0xAE); //Display off

    sleep_ms(100);

    write_command_arg(0xD5, 0x80); //Set clock divider
    write_command_arg(0xA8, 0x3F); //Enable all 64 rows
    write_command_arg(0xD3, 0x00); //zero row offset
    write_command_arg(0xAD, 0x8B); //Set charge pump
    
    write_command(0xA1); //no segment remap
    write_command(0xC8); //set scan direction

    write_command_arg(0xDA, 0x12); //Set com pins hardware config
    write_command_arg(0x81, 0xFF); //Set contrast to 255
    write_command_arg(0xD9, 0x1F); //Set dis-charge and pre-charge periods
    write_command_arg(0xDB, 0x40); //Set VCOM deslect

    write_command(0x33); //Set VPP 9V
    write_command(0xA6); //non-inverted

}

static void clear_display(){
    //clear the display
    for(int j = 0; j < 8; j++){
        write_command(0xB0 | j);
        
        //Display is centered with 2x non-visible pixels on each side 
        write_data(0);
        write_data(0);

        for(int i = 0; i < 16*8; i++){
            write_data(0);
        }

        write_data(0);
        write_data(0);
    }
}

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

    //init SPI @ 1MHz
    spi_init(spi_default, 1 * 1000 * 1000);
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

}

const size_t PAGE_ROW_COUNT = 8;
const size_t PAGE_COLUMN_COUNT = 128;
const size_t PAGE_COUNT = 8; 
uint8_t display_buffer[8 * 128];

int main() {

    bi_decl(bi_program_name("display test"));
    bi_decl(bi_program_description("test driving the oled display on the macropad board"));

    init_pins();

    stdio_init_all();

    init_display();

    clear_display();

    write_command(0xAF); //display on

    sleep_ms(100);

    //https://www.dafont.com/dogica.font
    //https://www.dafont.com/pixelmix.font
    const uint8_t font[] = {
        0b11111100, 0b00100010, 0b00100010, 0b00100010, 0b11111100, //A
        0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b01101100, //B
        0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01000100, //C
        0b11111110, 0b10000010, 0b10000010, 0b10000010, 0b01111100, //D
        0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b10000010, //E
        0b11111110, 0b00010010, 0b00010010, 0b00010010, 0b00000010, //F
        0b01111100, 0b10000010, 0b10000010, 0b10010010, 0b11110010, //G
        0b11111110, 0b00010000, 0b00010000, 0b00010000, 0b11111110, //H
        0b00000000, 0b10000010, 0b11111110, 0b10000010, 0b00000000, //I
        0b10000010, 0b10000010, 0b01111110, 0b00000010, 0b00000000, //J
        0b11111110, 0b00010000, 0b00101000, 0b01000100, 0b10000010, //K
        0b11111110, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //L
        0b11111110, 0b00000100, 0b00011000, 0b00000100, 0b11111110, //M
        0b11111110, 0b00001000, 0b00010000, 0b00100000, 0b11111110, //N
        0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100, //O
        0b11111110, 0b00010010, 0b00010010, 0b00010010, 0b00001100, //P
        0b01111100, 0b10000010, 0b10100010, 0b01000010, 0b10111100, //Q
        0b11111110, 0b00010010, 0b00010010, 0b00110010, 0b11001100, //R
        0b01001100, 0b10010010, 0b10010010, 0b10010010, 0b01100100, //S
        0b00000010, 0b00000010, 0b11111110, 0b00000010, 0b00000010, //T
        0b01111110, 0b10000000, 0b10000000, 0b10000000, 0b01111110, //U
        0b00011110, 0b01100000, 0b10000000, 0b01100000, 0b00011110, //V
        0b01111110, 0b10000000, 0b01110000, 0b10000000, 0b01111110, //W
        0b11000110, 0b00101000, 0b00010000, 0b00101000, 0b11000110, //X
        0b00001110, 0b00010000, 0b11100000, 0b00010000, 0b00001110, //Y
        0b11000010, 0b10100010, 0b10010010, 0b10001010, 0b10000110, //Z
    };

    absolute_time_t next_frame = make_timeout_time_us(16667);

    while(true){

         for(size_t c = 0; c < 26; c++){
            for(size_t i = 0; i < 5; i++){
             display_buffer[c*6 + i] = font[c*5+i];
            }
            display_buffer[c*6 + 6] = 0x0;
         }

        busy_wait_until(next_frame);
        next_frame = make_timeout_time_us(16667);

        for(size_t page = 0; page < PAGE_COUNT; page++){
            write_command(0xB0 | page);

            write_data(0);
            write_data(0);

            for(size_t col = 0; col < PAGE_COLUMN_COUNT; col++){
                write_data(display_buffer[(page * PAGE_COLUMN_COUNT) + col]);
            }

            write_data(0);
            write_data(0);
        }

        
    }
}