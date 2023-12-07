//operations_module.c

#include "includes.h"
#include "dht11_module.h"
#include"dht11.h"
#include"display.h"
#include "display_module.h"
#include "DownLinkDTO.h"
#include "wifi.h"
#include "wifi_module.h"
#include <stdio.h>
#include "cJSON.h"
#include "UpLinkDTO.h"
#include <stdio.h>


// Function to get a test DownLinkDTO (replace this with actual logic)
DownLinkDTO* getTestDownLinkDTO() {
    DownLinkDTO* testDownLinkDTO = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    if (testDownLinkDTO != NULL) {
        testDownLinkDTO->temperature_limit_high = 24;
        testDownLinkDTO->temperature_limit_low = 22;
        testDownLinkDTO->humidity_limit_high = 40;
        testDownLinkDTO->humidity_limit_low = 40;
        testDownLinkDTO->servo_limit_high = 180;
        testDownLinkDTO->servo_normal = 90;
        testDownLinkDTO->servo_limit_low = 0;
    }
    return testDownLinkDTO;
}


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


        // Get a test DownLinkDTO (replace this with actual logic)
        // DownLinkDTO* downlinkDto = deserializeDownLinkDTO(serverResponseJsonString);
        DownLinkDTO* downlinkDto = getTestDownLinkDTO();

        // Serialize DownLinkDTO to JSON
        cJSON* downlinkJson = serializeDownLinkDTO(downlinkDto);




        // Clean up
        cJSON_Delete(uplinkJson);
        free(uplinkDto);
        free (serializeUpLinkDTO);

        cJSON_Delete(downlinkJson);
        free(downlinkDto);
        
    }

}
