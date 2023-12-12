#include "operations_module.h"


// Assuming device_UID is a string, adjust the type accordingly
char device_UID[] = "SHSDIG9988";

// Assuming a global variable to store the server response
extern char serverResponseJsonString[MAX_RESPONSE_LENGTH];  // Extern declaration

// Function to get a test DownLinkDTO (replace this with actual logic)
DownLinkDTO* getTestDownLinkDTO() {
    DownLinkDTO* testDownLinkDTO = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    if (testDownLinkDTO != NULL) {
        // testDownLinkDTO->temperature_limit_high = 24;
        // testDownLinkDTO->temperature_limit_low = 22;
        // testDownLinkDTO->humidity_limit_high = 40;
        // testDownLinkDTO->humidity_limit_low = 40;
        // testDownLinkDTO->servo_limit_high = 180;
        // testDownLinkDTO->servo_normal = 90;
        // testDownLinkDTO->servo_limit_low = 0;
        testDownLinkDTO ->device_UID;
        testDownLinkDTO ->servo_angle = 90;
        
    }
    return testDownLinkDTO;
}

void initializeSensors() {
    tone_init();
    // Change the function call to initialize the servo module
    tone_play_windows_xp_startup();
    initServo();

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
        
        // Get a test DownLinkDTO (replace this with actual logic)

        //DownLinkDTO* downlinkDto = deserializeDownLinkDTO(serverResponseJsonString);
        DownLinkDTO* downlinkDto = getTestDownLinkDTO();

    

        // Serialize DownLinkDTO to JSON
        cJSON* downlinkJson = serializeNewDownLinkDTO(downlinkDto);

        // Move servo based on conditions
        //moveServoModuleBasedOnConditions(temperature_integer, humidity_integer, downlinkDto);
       moveNewAngle(downlinkDto);
        

        // Deserialize DownLinkDTO from JSON (if needed)
        DownLinkDTO* deserializedNewDownlinkDto = deserializeNewDownLinkDTO(downlinkJson);

        // Clean up
        cJSON_Delete(uplinkJson);
        cJSON_Delete(downlinkJson);
        free(downlinkDto);
        free(deserializedNewDownlinkDto);  // Free if deserializedDownlinkDto was used
    }
}