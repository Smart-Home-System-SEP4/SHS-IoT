#include "unity.h"
#include "UpLinkDTO.h"

void setUp(void) {
    // Set up any necessary initialization
}

void tearDown(void) {
    // Clean up any resources
}

void test_CreateUpLinkDTO(void) {
    // Arrange
    const char* testUID = "TEST1234";
    uint8_t tempInt = 25;
    uint8_t tempDec = 5;
    uint8_t humInt = 50;

    // Act
    UpLinkDTO* dto = createUpLinkDTO(tempInt, tempDec, humInt, testUID);

    // Assert
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempInt, dto->temperature_integer, "Temperature integer not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempDec, dto->temperature_decimal, "Temperature decimal not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humInt, dto->humidity_integer, "Humidity not set correctly");

    // Clean up
    free(dto);
}

void test_SerializeUpLinkDTO(void) {
    // Arrange
    const char* testUID = "TEST1234";
    uint8_t tempInt = 25;
    uint8_t tempDec = 5;
    uint8_t humInt = 50;

    UpLinkDTO* dto = createUpLinkDTO(tempInt, tempDec, humInt, testUID);

    // Act
    cJSON* json = serializeUpLinkDTO(dto);

    // Assert
    TEST_ASSERT_NOT_NULL_MESSAGE(json, "JSON serialization failed");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, cJSON_GetObjectItemCaseSensitive(json, "device_UID")->valuestring, "Device UID not serialized correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(tempInt, cJSON_GetObjectItemCaseSensitive(json, "temperature_integer")->valueint, "Temperature integer not serialized correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(tempDec, cJSON_GetObjectItemCaseSensitive(json, "temperature_decimal")->valueint, "Temperature decimal not serialized correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(humInt, cJSON_GetObjectItemCaseSensitive(json, "humidity_percentage")->valueint, "Humidity not serialized correctly");

    // Clean up
    cJSON_Delete(json);
    free(dto);
}

int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_CreateUpLinkDTO);
    RUN_TEST(test_SerializeUpLinkDTO);

    return UNITY_END();
}
