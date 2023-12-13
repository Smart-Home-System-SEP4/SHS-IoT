#include "unity.h"
#include "DownLinkDTO.h"
#include "../fff.h"

DEFINE_FFF_GLOBALS;

// Declare the fake functions
FAKE_VALUE_FUNC2(DownLinkDTO*, createNewDownLinkDTO, const char*, uint8_t);
FAKE_VALUE_FUNC1(cJSON*, serializeNewDownLinkDTO, const DownLinkDTO*);
FAKE_VALUE_FUNC1(DownLinkDTO*, deserializeNewDownLinkDTO, const cJSON*);

FAKE_VALUE_FUNC8(DownLinkDTO*, createDownLinkDTO, const char*, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
FAKE_VALUE_FUNC1(cJSON*, serializeDownLinkDTO, const DownLinkDTO*);
FAKE_VALUE_FUNC1(DownLinkDTO*, deserializeDownLinkDTO, const cJSON*);

void setUp(void) {
    // Set up any necessary initialization
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_CreateNewDownLinkDTO(void) {
    const char* testUID = "TEST1234";
    uint8_t servoAngle = 90;

    createNewDownLinkDTO_fake.return_val = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    TEST_ASSERT_NOT_NULL_MESSAGE(createNewDownLinkDTO_fake.return_val, "Memory allocation failed");

    strncpy(createNewDownLinkDTO_fake.return_val->device_UID, testUID, sizeof(createNewDownLinkDTO_fake.return_val->device_UID) - 1);
    createNewDownLinkDTO_fake.return_val->device_UID[sizeof(createNewDownLinkDTO_fake.return_val->device_UID) - 1] = '\0';
    createNewDownLinkDTO_fake.return_val->servo_angle = servoAngle;

    DownLinkDTO* dto = createNewDownLinkDTO(testUID, servoAngle);
    //Assert
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");
    TEST_ASSERT_NOT_NULL_MESSAGE(dto->device_UID, "Device UID pointer is NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoAngle, dto->servo_angle, "Servo angle not set correctly");
}

void test_SerializeNewDownLinkDTO(void) {
    const char* testUID = "TEST1234";
    uint8_t servoAngle = 90;

    serializeNewDownLinkDTO_fake.return_val = cJSON_CreateObject();

    DownLinkDTO* dto = createNewDownLinkDTO(testUID, servoAngle);
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");

    cJSON* json = serializeNewDownLinkDTO(dto);
    TEST_ASSERT_NOT_NULL_MESSAGE(json, "Serialized JSON is NULL");

    char* jsonString = cJSON_PrintUnformatted(json);
    TEST_ASSERT_NOT_NULL_MESSAGE(jsonString, "JSON string is NULL");
    TEST_ASSERT_GREATER_THAN_INT_MESSAGE(0, strlen(jsonString), "JSON string is empty");

    // Free the cJSON string
    free(jsonString);
}


void test_DeserializeNewDownLinkDTO(void) {
    const char* testUID = "TEST1234";
    uint8_t servoAngle = 90;

    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "device_UID", testUID);
    cJSON_AddItemToObject(json, "servo_angle", cJSON_CreateNumber(servoAngle));

    deserializeNewDownLinkDTO_fake.return_val = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    TEST_ASSERT_NOT_NULL_MESSAGE(deserializeNewDownLinkDTO_fake.return_val, "Memory allocation failed");

    strncpy(deserializeNewDownLinkDTO_fake.return_val->device_UID, testUID, sizeof(deserializeNewDownLinkDTO_fake.return_val->device_UID) - 1);
    deserializeNewDownLinkDTO_fake.return_val->device_UID[sizeof(deserializeNewDownLinkDTO_fake.return_val->device_UID) - 1] = '\0';
    deserializeNewDownLinkDTO_fake.return_val->servo_angle = servoAngle;

    DownLinkDTO* dto = deserializeNewDownLinkDTO(json);
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO deserialization failed");
    TEST_ASSERT_NOT_NULL_MESSAGE(dto->device_UID, "Device UID pointer is NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoAngle, dto->servo_angle, "Servo angle not set correctly");

    // Free the allocated memory
    free(dto);
    cJSON_Delete(json);
}












//Not Used by Cloud-Team
void test_CreateDownLinkDTO(void) {
    const char* testUID = "TEST1234";
    uint8_t tempLimitHigh = 30;
    uint8_t tempLimitLow = 10;
    uint8_t humLimitHigh = 80;
    uint8_t humLimitLow = 20;
    uint8_t servoLimitHigh = 180;
    uint8_t servoNormal = 90;
    uint8_t servoLimitLow = 0;

    createDownLinkDTO_fake.return_val = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    TEST_ASSERT_NOT_NULL_MESSAGE(createDownLinkDTO_fake.return_val, "Memory allocation failed");

    strncpy(createDownLinkDTO_fake.return_val->device_UID, testUID, sizeof(createDownLinkDTO_fake.return_val->device_UID) - 1);
    createDownLinkDTO_fake.return_val->device_UID[sizeof(createDownLinkDTO_fake.return_val->device_UID) - 1] = '\0';
    createDownLinkDTO_fake.return_val->temperature_limit_high = tempLimitHigh;
    createDownLinkDTO_fake.return_val->temperature_limit_low = tempLimitLow;
    createDownLinkDTO_fake.return_val->humidity_limit_high = humLimitHigh;
    createDownLinkDTO_fake.return_val->humidity_limit_low = humLimitLow;
    createDownLinkDTO_fake.return_val->servo_limit_high = servoLimitHigh;
    createDownLinkDTO_fake.return_val->servo_normal = servoNormal;
    createDownLinkDTO_fake.return_val->servo_limit_low = servoLimitLow;

    DownLinkDTO* dto = createDownLinkDTO(testUID, tempLimitHigh, tempLimitLow, humLimitHigh, humLimitLow, servoLimitHigh, servoNormal, servoLimitLow);

    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");
    TEST_ASSERT_NOT_NULL_MESSAGE(dto->device_UID, "Device UID pointer is NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempLimitHigh, dto->temperature_limit_high, "Temperature limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempLimitLow, dto->temperature_limit_low, "Temperature limit low not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humLimitHigh, dto->humidity_limit_high, "Humidity limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humLimitLow, dto->humidity_limit_low, "Humidity limit low not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoLimitHigh, dto->servo_limit_high, "Servo limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoNormal, dto->servo_normal, "Servo normal not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoLimitLow, dto->servo_limit_low, "Servo limit low not set correctly");
}

void test_SerializeDownLinkDTO(void) {
    // Implement tests for serializeDownLinkDTO similar to test_SerializeNewDownLinkDTO
    const char* testUID = "TEST1234";
    uint8_t tempLimitHigh = 30;
    uint8_t tempLimitLow = 10;
    uint8_t humLimitHigh = 80;
    uint8_t humLimitLow = 20;
    uint8_t servoLimitHigh = 180;
    uint8_t servoNormal = 90;
    uint8_t servoLimitLow = 0;

    serializeDownLinkDTO_fake.return_val = cJSON_CreateObject();

    DownLinkDTO* dto = createDownLinkDTO(testUID, tempLimitHigh, tempLimitLow, humLimitHigh, humLimitLow, servoLimitHigh, servoNormal, servoLimitLow);
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");

    cJSON* json = serializeDownLinkDTO(dto);
    TEST_ASSERT_NOT_NULL_MESSAGE(json, "Serialized JSON is NULL");

    char* jsonString = cJSON_PrintUnformatted(json);
    TEST_ASSERT_NOT_NULL_MESSAGE(jsonString, "JSON string is NULL");
    TEST_ASSERT_GREATER_THAN_INT_MESSAGE(0, strlen(jsonString), "JSON string is empty");

    // Free the cJSON string
    free(jsonString);
}

void test_DeserializeDownLinkDTO(void) {
    const char* testUID = "TEST1234";
    uint8_t tempLimitHigh = 30;
    uint8_t tempLimitLow = 10;
    uint8_t humLimitHigh = 80;
    uint8_t humLimitLow = 20;
    uint8_t servoLimitHigh = 180;
    uint8_t servoNormal = 90;
    uint8_t servoLimitLow = 0;

    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "device_UID", testUID);
    cJSON_AddItemToObject(json, "temperature_limit_high", cJSON_CreateNumber(tempLimitHigh));
    cJSON_AddItemToObject(json, "temperature_limit_low", cJSON_CreateNumber(tempLimitLow));
    cJSON_AddItemToObject(json, "humidity_limit_high", cJSON_CreateNumber(humLimitHigh));
    cJSON_AddItemToObject(json, "humidity_limit_low", cJSON_CreateNumber(humLimitLow));
    cJSON_AddItemToObject(json, "servo_limit_high", cJSON_CreateNumber(servoLimitHigh));
    cJSON_AddItemToObject(json, "servo_normal", cJSON_CreateNumber(servoNormal));
    cJSON_AddItemToObject(json, "servo_limit_low", cJSON_CreateNumber(servoLimitLow));

    deserializeDownLinkDTO_fake.return_val = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));
    TEST_ASSERT_NOT_NULL_MESSAGE(deserializeDownLinkDTO_fake.return_val, "Memory allocation failed");


    strncpy(deserializeDownLinkDTO_fake.return_val->device_UID, testUID, sizeof(deserializeDownLinkDTO_fake.return_val->device_UID) - 1);
    deserializeDownLinkDTO_fake.return_val->device_UID[sizeof(deserializeDownLinkDTO_fake.return_val->device_UID) - 1] = '\0';
    deserializeDownLinkDTO_fake.return_val->temperature_limit_high = cJSON_GetObjectItemCaseSensitive(json, "temperature_limit_high")->valueint;
    deserializeDownLinkDTO_fake.return_val->temperature_limit_low = cJSON_GetObjectItemCaseSensitive(json, "temperature_limit_low")->valueint;
    deserializeDownLinkDTO_fake.return_val->humidity_limit_high = cJSON_GetObjectItemCaseSensitive(json, "humidity_limit_high")->valueint;
    deserializeDownLinkDTO_fake.return_val->humidity_limit_low = cJSON_GetObjectItemCaseSensitive(json, "humidity_limit_low")->valueint;
    deserializeDownLinkDTO_fake.return_val->servo_limit_high = cJSON_GetObjectItemCaseSensitive(json, "servo_limit_high")->valueint;
    deserializeDownLinkDTO_fake.return_val->servo_normal = cJSON_GetObjectItemCaseSensitive(json, "servo_normal")->valueint;
    deserializeDownLinkDTO_fake.return_val->servo_limit_low = cJSON_GetObjectItemCaseSensitive(json, "servo_limit_low")->valueint;

    DownLinkDTO* dto = deserializeDownLinkDTO(json);
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO deserialization failed");
    TEST_ASSERT_NOT_NULL_MESSAGE(dto->device_UID, "Device UID pointer is NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempLimitHigh, dto->temperature_limit_high, "Temperature limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempLimitLow, dto->temperature_limit_low, "Temperature limit low not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humLimitHigh, dto->humidity_limit_high, "Humidity limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humLimitLow, dto->humidity_limit_low, "Humidity limit low not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoLimitHigh, dto->servo_limit_high, "Servo limit high not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoNormal, dto->servo_normal, "Servo normal not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(servoLimitLow, dto->servo_limit_low, "Servo limit low not set correctly");

    // Free the allocated memory
    free(dto);
    cJSON_Delete(json);
}




int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_CreateNewDownLinkDTO);
    RUN_TEST(test_SerializeNewDownLinkDTO);
    RUN_TEST(test_DeserializeNewDownLinkDTO);
    RUN_TEST(test_CreateDownLinkDTO);
    RUN_TEST(test_SerializeDownLinkDTO);
    RUN_TEST(test_DeserializeDownLinkDTO);

    return UNITY_END();
}
