// Tue 29 Mar 17:58:24 UTC 2022 - ONLINE edit

// PRESERVED WIRING VERTICAL TARGET ORIENTATION

#if 0
// we are pico-sdk not Arduino IDE

// RS E D4 D5 D6 D7

#include <LiquidCrystal.h>

LiquidCrystal lcd(
 21, // RS blue   to Uno:D12 pico:GP21
 20, //  E purple to Uno:D11 pico:GP20
 // 4-bit data bus:
 19, // D4 green  to Uno:D10 pico:GP19
 18, // D5 brown  to Uno:D9  pico:GP18
 17, // D6 gold   to Uno:D8  pico:GP17
 16  // D7 gray   to Uno:D7  pico:GP16
);

// Connect K Kathode to GND
// Connect Uno:5 Volts to A Anode via 330 Ohms
#endif


/* rp2040 */
#include <stdio.h>
#include <string.h> // strcpy
#include "pico/stdio.h"
#include "pico/stdlib.h"

#define stack_buffer_length 64

#if CONF_USBD_HS_SP
#define CDCD_ECHO_BUF_SIZCF CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ_HS
#else
#define TEST_CBC77 1
#endif

char print_stringxx[stack_buffer_length];

#define RP2040_PICO
#ifdef RP2040_PICO

#define DATE_STAMP "Mon 28 Mar 23:31:49 UTC 2022"
#define BRANCH_STAMP  "dvlp-aa                            __"
#define COMMIT_STAMP  "49723cf"
#define FEATURE_STAMP "+wokwi +auto_load +rewind            "
#define MODE_STAMP "copy_to_ram"
#define VERS_CFORTH ("\103CamelForth in C v0.1 - 14 Feb 2016 - " DATE_STAMP "  ");
#define DOFILLS_datus ("\237\n\n " FEATURE_STAMP DATE_STAMP " \n branch " BRANCH_STAMP " " COMMIT_STAMP " UNDER TEST   \n " MODE_STAMP " mode\n\n");

#include <stdint.h>
#include <stdbool.h>

#define RP2040_PICO               /* for use with Raspberry Pi Pico RP2040 based target */
#define USB_IFACE                 /* only some implementations */

uint32_t getFlKey_counterLCL = 0;

#ifdef RP2040_PICO

uint8_t getKey(void) {     // hardware-independent wrapper xa
    uint8_t ch_read;
    do {
        ch_read = getchar_timeout_us(18); // 4 tries per 87 uSec char window at 115200 bps
    } while ((ch_read == '\0') || (ch_read == 0xff));
    return ch_read;
}

void queryKey(void) {
}

#define FL_KEY_BASE 0x10040000 // same as example code SDK // xcc

#define BUFFLEN 128
#define CHOP_LN 5

char instringLCL[BUFFLEN];
char tempstringLCL[BUFFLEN];

void init_cutterLCL(void) {
    strcpy(instringLCL, print_stringxx);
}

/*
 *      Remove given section from string. Negative len means remove
 *      everything up to the end. xc
 */

int str_cutLCL(char *str, int begin, int len) {
    int l = strlen(str);

    if (len < 0)
        len = l - begin;
    if (begin + len > l)
        len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}

void slowerLCL(void) {
    for (volatile int i = 1295; i > 0; i--) {
    }
}

void printf_cutterLCL(void) {
    putchar('c'); // cdcdf_acm_write((uint8_t *) tempstringLCL, strlen(tempstringLCL));
    slowerLCL();                   // no ringbuffer - kludge
}

void do_outputLCL(void) {
    printf_cutterLCL();
}

void slicerLCL(char *instringLCL) {
    tempstringLCL[0] = '\0';
    tempstringLCL[1] = '\0';

    int origin = 0;
    int chopln = CHOP_LN;       // chop length
    int to_end = -1;

    int l = (strlen(instringLCL) / chopln);

    for (int index = 1; index < (l + 1); index++) {
        int j = chopln * index;
        int k = j - chopln;
        strcpy(tempstringLCL, instringLCL);
        str_cutLCL(tempstringLCL, j, to_end);
        if (index > 1) {
            str_cutLCL(tempstringLCL, origin, k);
        }
        do_outputLCL();
    }

    if ((strlen(instringLCL)) > ((strlen(instringLCL) / chopln) * chopln)) {
        strcpy(tempstringLCL, instringLCL);
        int c = l * chopln;
        str_cutLCL(tempstringLCL, 0, c);
        do_outputLCL();
    }

}

void cut_mainLCL(void) {
    init_cutterLCL();
    slicerLCL(instringLCL);
}

// primary api is chopped_acm_writeLCL(print_stringxx) from caller

// void chopped_acm_writeLCL(char *str) {
void chopped_acm_writeLCL() {
    cut_mainLCL();
}

#ifdef NEVER_DEFINED_EVER
/*

Stack Overflow

permalink:

 [ https://stackoverflow.com/a/20346241 ]

other link:

 [ https://stackoverflow.com/questions/20342559/how-to-cut-part-of-a-string-in-c ]

The following function cuts a given range out of a char buffer.
The range is identified by startng index and length. A negative
length may be specified to indicate the range from the starting
index to the end of the string.
*/

/*
 *      Remove given section from string. Negative len means
 *      remove everything up to the end.
 */

int str_cutLCL(char *str, int begin, int len) {
    int l = strlen(str);

    if (len < 0)
        len = l - begin;
    if (begin + len > l)
        len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}

/*

The char range is cut out by moving everything after the
range including the terminating '\0' to the starting index
with memmove, thereby overwriting the range. The text in
the range is lost.

Note that you need to pass a char buffer whose contents
can be changed. Don't pass string literals that are stored
in read-only memory.

answered Dec 3 '13 at 8:33
M Oehm

site design / logo © 2018 Stack Exchange Inc;
user contributions
licensed under cc by-sa 3.0 with attribution required.
rev 2018.9.14.31567
*/
#endif // #ifdef NEVER_DEFINED_EVER

/*
 * Terminal I/O functions
 */

int length_print_stringXLCL = 0;    // would like to shed this global

/* USB based */
#ifdef NOT_DEFINED_RP2040
#define printf(format,integer) \
    length_print_stringXLCL = 0; \
    print_stringxx[0] = (uint32_t) "\0"; \
    sprintf(print_stringxx, format, integer); \
    length_print_stringXLCL = strlen(print_stringxx); \
        chopped_acm_writeLCL(print_stringxx)
#endif // not defined rp2040

#define getch getKey // keep rp2040


/* replace with a new version Fri 12 Feb 2021 01:27 33: */
void putchLCL(char c) {
    char *p;
    p = &c;
    c = *p +0;
    print_stringxx[0] = c;
    print_stringxx[1] = '\0';
    printf("%s", print_stringxx);
}

int getqueryXLCL(void) {
    return -1;                  /* TODO wa1tnr */
}

#endif

#define READING_SIZE 4096

char dofilldatusXLCL[] = DOFILLS_datus

void crufty_printerXLCL(void) {
    printf("%s", dofilldatusXLCL);
}

#include "pico/bootrom.h"
#endif

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

extern void interpreter(void);
extern void _pico_LED_init(void);

int main() {
    sleep_ms(100);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    _pico_LED_init();  // new 20 March

    // uart_putc_raw(UART_ID, 'A');

    sleep_ms(100);
    uart_puts(UART_ID, "\r\nnew wokwi RPi Pico RP2040  Forth 29 Mar 2022\r\n\r\n");

    uart_puts(UART_ID, " pico-sdk  based\r\n\r\n");

    putchar(' ');
    putchar(' ');
    putchar('4');
    putchar('-');
    putchar('b');
    putchar('i');
    putchar('t');
    putchar(' ');
    putchar('L');
    putchar('C');
    putchar('D');
    putchar(' ');
    putchar('F');
    putchar('o');
    putchar('r');
    putchar('t');
    putchar('h');
    putchar(' ');
    putchar('\r');
    putchar('\n');
//                          123456789012345678901234567890123456789012345678901234567890
    strcpy(print_stringxx, "  greet  Wed 20 Mar 23:36:16 UTC 2024 - wokwi vscode extn\n");
    printf("%s", print_stringxx);
    strcpy(print_stringxx, "  .s dump cold .. depth char decimal hex added\n");
    printf("%s", print_stringxx);
    strcpy(print_stringxx, "  Opening work day for Thursday 21 March 13:08:52 UTC 2024\n");
    printf("%s", print_stringxx);

    putchar('\n');

    while(-1) {
        interpreter();
    }

    strcpy(print_stringxx, "  rut-roh  Wed 20 Mar 20:45:51 UTC 2022");

    while(1) {
        uint8_t ch_key = getKey();
        putchar(ch_key); // seems okay - no further research yet
    }
}

/// \end::hello_uart[]
