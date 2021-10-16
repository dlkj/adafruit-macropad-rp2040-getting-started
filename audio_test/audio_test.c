
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/structs/clocks.h"

#include "pico/audio_pwm.h"

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256

static int16_t sine_wave_table[SINE_WAVE_TABLE_LEN];

struct audio_buffer_pool *init_audio() {

    static audio_format_t audio_format = {
            .format = AUDIO_BUFFER_FORMAT_PCM_S16,
            .sample_freq = 24000,
            .channel_count = 1,
    };

    static struct audio_buffer_format producer_format = {
            .format = &audio_format,
            .sample_stride = 2
    };

    struct audio_buffer_pool *producer_pool = audio_new_producer_pool(&producer_format, 3,
                                                                      SAMPLES_PER_BUFFER); // todo correct size
    bool __unused ok;
    const struct audio_format *output_format;

    audio_pwm_channel_config_t conf = default_mono_channel_config;
    conf.core.base_pin = ADAFRUIT_MACROPAD_SPEAKER_PIN;

    output_format = audio_pwm_setup(&audio_format, -1, &conf);
    if (!output_format) {
        panic("PicoAudio: Unable to open audio device.\n");
    }
    ok = audio_pwm_default_connect(producer_pool, false);
    assert(ok);
    audio_pwm_set_enabled(true);
    return producer_pool;
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

    gpio_init(ADAFRUIT_MACROPAD_SPEAKER_ENABLE_PIN);
    //gpio_init(ADAFRUIT_MACROPAD_SPEAKER_PIN);

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

    gpio_set_dir(ADAFRUIT_MACROPAD_SPEAKER_ENABLE_PIN, GPIO_OUT);
    //gpio_set_dir(ADAFRUIT_MACROPAD_SPEAKER_PIN, GPIO_OUT);

}



int main() {

    bi_decl(bi_program_name("audio test"));
    bi_decl(bi_program_description("test audio on the macropad board"));

    init_pins();

    stdio_init_all();

    set_sys_clock_48mhz();

    //enable the speaker amplifier
    gpio_put(ADAFRUIT_MACROPAD_SPEAKER_ENABLE_PIN, true);

    // while(true){

    //     gpio_put(ADAFRUIT_MACROPAD_SPEAKER_ENABLE_PIN, !gpio_get(ADAFRUIT_MACROPAD_BUTTON_PIN));

    //     gpio_put(ADAFRUIT_MACROPAD_SPEAKER_PIN, false);

    //     sleep_ms(1);

    //     gpio_put(ADAFRUIT_MACROPAD_SPEAKER_PIN, true);

    //     sleep_ms(1);

    // }

    for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
        sine_wave_table[i] = 32767 * cosf(i * 2 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
    }

    struct audio_buffer_pool *ap = init_audio();
    uint32_t step = 0x200000;
    uint32_t pos = 0;
    uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;
    uint vol = 128;

    printf("pin = %d\r", PICO_AUDIO_PWM_MONO_PIN);

    while (true) {

        enum audio_correction_mode m = audio_pwm_get_correction_mode();

        int c = getchar_timeout_us(0);
        if (c >= 0) {
            if (c == '-' && vol) vol -= 4;
            if ((c == '=' || c == '+') && vol < 255) vol += 4;
            if (c == '[' && step > 0x10000) step -= 0x10000;
            if (c == ']' && step < (SINE_WAVE_TABLE_LEN / 16) * 0x20000) step += 0x10000;
            if (c == 'q') break;

            if (c == 'c') {
                bool done = false;
                while (!done) {
                    if (m == none) m = fixed_dither;
                    else if (m == fixed_dither) m = dither;
                    else if (m == dither) m = noise_shaped_dither;
                    else if (m == noise_shaped_dither) m = none;
                    done = audio_pwm_set_correction_mode(m);
                }
            }
            printf("vol = %d, step = %d mode = %d      \r", vol, step >>16, m);
        }
        struct audio_buffer *buffer = take_audio_buffer(ap, true);
        int16_t *samples = (int16_t *) buffer->buffer->bytes;
        for (uint i = 0; i < buffer->max_sample_count; i++) {
            samples[i] = (vol * sine_wave_table[pos >> 16u]) >> 8u;
            pos += step;
            if (pos >= pos_max) pos -= pos_max;
        }
        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(ap, buffer);
    }
    puts("\n");
    return 0;

}