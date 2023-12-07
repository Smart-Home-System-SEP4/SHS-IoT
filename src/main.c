#include "includes.h"
#include "dht11.h"
#include "display.h"
#include "leds.h"
#include "light.h"
#include "buzzer.h"
#include "buttons.h"
#include "periodic_task.h"
#include "adxl345.h"
#include "hc_sr04.h"
#include "wifi.h"
#include "avr/power.h"
#include "pir.h"
#include "tone.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h> // Include the interrupt header
#include <stdio.h>
#include"dht11_module.h"
int main(void) {
    // Initialize UART for USART0, configure baud rate and callback (if needed).
    uart_init(USART_0, 9600, NULL);

    // Enable global interrupts.
    sei();

    dht11_init(); // Initialize the DHT11 sensor

    while (1) {
        uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;
        char str[64];

        if (readDHT11DataWithRetry(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal)) {
            snprintf(str, sizeof(str), "Humidity = %d.%d%% and the temperature = %d.%d C\n\n", 
                humidity_integer, humidity_decimal, temperature_integer, temperature_decimal);

            // Transmit the message over UART
            uart_send_string_blocking(USART_0, str);
        } else {
            uart_send_string_blocking(USART_0, "Failed to read DHT11 data\n");
        }

        // Delay before the next DHT11 sensor reading
        _delay_ms(2000);
    }
    return 0;
}