#include "rp2040_pico.h"
#include "pico/stdlib.h"

// TODO: renamed to getKeyUSB() wonder what that breaks 20 March
uint8_t getKeyUSB(void) {     // hardware-independent wrapper
    uint8_t ch_read;
    int count=0;
    int flip;
    // const uint LED_PIN = 25; // hard-coded for RPi Pico RP2040 only - needs update for multiple targets
    const uint LED_PIN = LED_PIN_MASTER;
    flip=-1;
    do {
        count++;
        //           0x1FFFF  every 3 seconds or so

        if (count == 0x3FFFF) { // every 20 seconds or so
            // printf("."); // suppress this except for testing
            count = 0;
            if (flip == -1) {
                gpio_put(LED_PIN, 1);
            //  for (volatile int i=2444; i>0; i--);
                for (volatile int i=KB_PIP_LN; i>0; i--);
                // sleep_ms(1);
                gpio_put(LED_PIN, 0);
            }
         // if (flip ==  0) { gpio_put(LED_PIN, 0); }
            int flop = flip;
            if (flop == -1) flip =  0;
            if (flop ==  0) flip = -1;
        }
        ch_read = getchar_timeout_us(18); // 4 tries per 87 uSec char window at 115200 bps
    } while ((ch_read == '\0') || (ch_read == 0xff));
    return ch_read;
}

// TODO: 20 March renamed to queryKeyUSB what does that if any break
// void queryKey(void) {
void queryKeyUSB(void) {
    // TODO wa1tnr
}
