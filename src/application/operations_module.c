//operations_module.c

#include "includes.h"
#include "dht11_module.h"
#include "display_module.h"
#include "wifi.h"
#include "wifi_module.h"
#include <stdio.h>
#include "cJSON.h"
#include "UpLinkDTO.h"



void initializeSensors() {

    // Initialize other sensors and communication modules
    dht11_init();
    display_init();
    initPCCommAndWiFi();
}

void performOperations() {
    // Sensor data variables
    uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;

    // Read sensor data with retry
    if (readDHT11DataWithRetry(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal)) {
        
        // Create UpLinkDTO
        UpLinkDTO* uplinkDto = createUpLinkDTO(temperature_integer, temperature_decimal, humidity_integer);

        // Serialize UpLinkDTO to JSON
        cJSON* uplinkJson = serializeUpLinkDTO(uplinkDto);

        // Send UpLinkDTO to WiFi
        sendDTO_to_WiFi(uplinkJson);

        // Display sensor data on the 7-segment display
        displayData(temperature_integer, temperature_decimal, humidity_integer);


        // Print UpLinkDTO content
        if (uplinkDto != NULL) {
            printf("UpLinkDTO - Temperature: %d.%d°C, Humidity: %d.%d%%",
                   uplinkDto->temperature_integer, uplinkDto->temperature_decimal,
                   uplinkDto->humidity_integer);
            free(uplinkDto);
        }

        // Clean up
        cJSON_Delete(uplinkJson);
        free(uplinkDto);
        free (serializeUpLinkDTO);

    }

}
