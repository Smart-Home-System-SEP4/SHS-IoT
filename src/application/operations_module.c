//operations_module.c

#include "includes.h"
#include "dht11_module.h"
#include "display_module.h"
#include "wifi.h"
#include "wifi_module.h"
#include <stdio.h>
#include "cJSON.h"
#include "UpLinkDTO.h"
#include "uid_constants.h"
#include "UpLinkDTO.h"
#include <stdio.h>






// Unique ID for device identification
char device_UID[] = "SHSDIG9988";

void initializeSensors() {

    // Initialize other sensors and communication modules
    dht11_init();
    display_init();
    initPCCommAndWiFi();

    // Initialize the device UID
    initializeDeviceUID();
}

void performOperations() {
    // Sensor data variables
    uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;

    // Read sensor data with retry
    if (readDHT11DataWithRetry(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal)) {
        
        // Create UpLinkDTO
        UpLinkDTO* uplinkDto = createUpLinkDTO(temperature_integer, temperature_decimal, humidity_integer, device_UID);

        // Serialize UpLinkDTO to JSON
        cJSON* uplinkJson = serializeUpLinkDTO(uplinkDto);

        // Send UpLinkDTO to WiFi
        sendDTO_to_WiFi(uplinkJson);

        // Display sensor data on the 7-segment display
        displayData(temperature_integer, temperature_decimal, humidity_integer);

        // Print UpLinkDTO content
        if (uplinkDto != NULL) {
            printf("UpLinkDTO - Temperature: %d.%d°C, Humidity: %d.%d%%, DeviceUID: %s\n",
                   uplinkDto->temperature_integer, uplinkDto->temperature_decimal,
                   uplinkDto->humidity_integer, uplinkDto->device_UID);
            free(uplinkDto);
        }

        // Clean up
        cJSON_Delete(uplinkJson);
        free(uplinkDto);
        free (serializeUpLinkDTO);

    }

}
