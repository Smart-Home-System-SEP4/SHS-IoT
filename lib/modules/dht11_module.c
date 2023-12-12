//dht11_module.c


#include "dht11_module.h"
<<<<<<< HEAD


=======
#include "dht11.h"
#include"uart.h"
>>>>>>> 5d90f8922071045b5b1d7cb5f61f1a73e2607635
int readDHT11DataWithRetry(uint8_t *humidity_integer, uint8_t *humidity_decimal, uint8_t *temperature_integer, uint8_t *temperature_decimal) {
    // Set the maximum number of retries and the delay between retries
    int maxRetries = 10;
    int retryDelay = 100;  // in milliseconds

    for (int retry = 0; retry < maxRetries; retry++) {
        if (dht11_get(humidity_integer, humidity_decimal, temperature_integer, temperature_decimal) == DHT11_OK) {
            return 1; // Success
        } 

        // Add a delay before the next retry
        _delay_ms(retryDelay);
    }

    return 0; // Failed to obtain readings within the specified retries
}
