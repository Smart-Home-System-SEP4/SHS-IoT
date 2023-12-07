//operations_module.c

#include "includes.h"
#include "dht11_module.h"
#include "display_module.h"
#include <stdio.h>

void initializeSensors() {
    // Initialize other sensors and communication modules
    dht11_init();
    display_init();
    
}

void performOperations() {
    // Sensor data variables
    uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;

    // Read sensor data with retry
    if (readDHT11DataWithRetry(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal)) {

        // Display sensor data on the 7-segment display
        displayData(temperature_integer, temperature_decimal, humidity_integer);
    }
}
