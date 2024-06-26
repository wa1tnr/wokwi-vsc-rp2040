/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
// #include "hardware/clocks.h"
// #include "ws2812.pio.h"
#include "generated/ws2812.pio.h"
#include "pico-hardware-camelforth.h" // NPX_PIN defined

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

/*
void pattern_snakes(uint len, uint t) {
    for (uint i = 0; i < len; ++i) {
        uint x = (i + (t >> 1)) % 64;
        if (x < 10)
            put_pixel(urgb_u32(0xff, 0, 0));
        else if (x >= 15 && x < 25)
            put_pixel(urgb_u32(0, 0xff, 0));
        else if (x >= 30 && x < 40)
            put_pixel(urgb_u32(0, 0, 0xff));
        else
            put_pixel(0);
    }
}

void pattern_random(uint len, uint t) {
    if (t % 8)
        return;
    for (int i = 0; i < len; ++i)
        put_pixel(rand());
}

void pattern_sparkle(uint len, uint t) {
    if (t % 8)
        return;
    for (int i = 0; i < len; ++i)
        put_pixel(rand() % 16 ? 0 : 0xffffffff);
}

void pattern_greys(uint len, uint t) {
    int max = 100; // let's not draw too much current!
    t %= max;
    for (int i = 0; i < len; ++i) {
        put_pixel(t * 0x10101);
        if (++t >= max) t = 0;
    }
}

*/

/*
typedef void (*pattern)(uint len, uint t);
const struct {
    pattern pat;
    const char *name;
} pattern_table[] = {
        {pattern_snakes,  "Snakes!"},
        {pattern_random,  "Random data"},
        {pattern_sparkle, "Sparkles"},
        {pattern_greys,   "Greys"},
};
*/

// QTPY NEOPIX is 12
// const int PIN_TX = 12; // was 0;
const int PIN_TX = NPX_PIN; // 16 // feather rp2040 GPIO16 NEOPIX
// const int PIN_TX = 17; // was 0;

extern void _pico_RGB_init(void);

void _this_ws2812() {
    //set_sys_clock_48();
    stdio_init_all();
    // puts("   WS2812 Smoke Test R 001a");
    printf("   WS2812 Smoke Test Rev 001e   nscrt     ");
     _pico_RGB_init();

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, PIN_TX, 800000, true);

    // int t = 0;
        // int pat = rand() % count_of(pattern_table);
        // int dir = (rand() >> 30) & 1 ? 1 : -1;
        // puts(pattern_table[pat].name);
        // puts(dir == 1 ? "(forward)" : "(backward)");

            // RGB

            put_pixel(urgb_u32(0x02, 0, 0x02)); // magenta
            sleep_ms(333);

            put_pixel(urgb_u32(0x02, 0, 0x02)); sleep_ms(333); put_pixel(0); sleep_ms(333);
            put_pixel(urgb_u32(0x02, 0, 0x02)); sleep_ms(333); put_pixel(0); sleep_ms(333);

            put_pixel(0); sleep_ms(22); sleep_ms(10);
            // t += dir;
}
