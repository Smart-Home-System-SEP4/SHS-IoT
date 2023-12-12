// display_module.c
#include "display.h"

#ifdef AVR_PLATFORM
    #include <util/delay.h>
    #define DELAY_MS(ms) _delay_ms(ms)
#else
    #define DELAY_MS(ms)
#endif

void displayData(uint8_t temperature_integer, uint8_t temperature_decimal, uint8_t humidity_integer) {
    // Break down the values for temperature integer
    uint8_t temp_int_tens = temperature_integer / 10;
    uint8_t temp_int_ones = temperature_integer % 10;

    // Break down the values for humidity integer
    uint8_t hum_int_tens = humidity_integer / 10;
    uint8_t hum_int_ones = humidity_integer % 10;

    display_setValues(temp_int_tens, temp_int_ones, 17, 12);
    DELAY_MS(4000); // Display for 4 seconds

    display_setValues(hum_int_tens, hum_int_ones, 17, 18); // Assuming 18 is for dot and 19 is for underscore
    DELAY_MS(4000); // Display for 4 seconds

    display_setValues(0, 0, 0, 0);
    DELAY_MS(1000); // Display for 1 second
}