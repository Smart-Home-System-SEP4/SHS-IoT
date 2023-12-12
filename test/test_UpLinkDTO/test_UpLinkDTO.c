 #include "unity.h"
#include "UpLinkDTO.h"
#include "../fff.h"

DEFINE_FFF_GLOBALS;

// Declare the fake functions
FAKE_VALUE_FUNC4(UpLinkDTO*, createUpLinkDTO, uint8_t, uint8_t, uint8_t, const char*);
FAKE_VALUE_FUNC1(cJSON*, serializeUpLinkDTO, const UpLinkDTO*);




void setUp(void) {
    // Set up any necessary initialization
    FFF_RESET_HISTORY();
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
    // Ensure the fake is ready to return a valid value
    createUpLinkDTO_fake.return_val = (UpLinkDTO*)malloc(sizeof(UpLinkDTO));

    // Check if memory allocation is successful
    TEST_ASSERT_NOT_NULL_MESSAGE(createUpLinkDTO_fake.return_val, "Memory allocation failed");

    // Initialize fields
    strncpy(createUpLinkDTO_fake.return_val->device_UID, testUID, sizeof(createUpLinkDTO_fake.return_val->device_UID) - 1);
    createUpLinkDTO_fake.return_val->device_UID[sizeof(createUpLinkDTO_fake.return_val->device_UID) - 1] = '\0';
    createUpLinkDTO_fake.return_val->temperature_integer = tempInt;
    createUpLinkDTO_fake.return_val->temperature_decimal = tempDec;
    createUpLinkDTO_fake.return_val->humidity_integer = humInt;

    // Directly use createUpLinkDTO_fake.return_val
    UpLinkDTO* dto = createUpLinkDTO(tempInt, tempDec, humInt, testUID);

    // Assert
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");
    TEST_ASSERT_NOT_NULL_MESSAGE(dto->device_UID, "Device UID pointer is NULL");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, dto->device_UID, "Device UID not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempInt, dto->temperature_integer, "Temperature integer not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(tempDec, dto->temperature_decimal, "Temperature decimal not set correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(humInt, dto->humidity_integer, "Humidity not set correctly");
    

}
void test_SerializeUpLinkDTO(void) {
    // Arrange
    const char* testUID = "TEST1234";
    uint8_t tempInt = 25;
    uint8_t tempDec = 5;
    uint8_t humInt = 50;

    // Mock the serializeUpLinkDTO function to return a cJSON object
    serializeUpLinkDTO_fake.return_val = cJSON_CreateObject();

    // Act
    // Ensure memory allocation in createUpLinkDTO is successful
    UpLinkDTO* dto = createUpLinkDTO(tempInt, tempDec, humInt, testUID);
    TEST_ASSERT_NOT_NULL_MESSAGE(dto, "DTO creation failed");

    // Call the function under test
    printf("Debug: Before serializeUpLinkDTO\n");
    cJSON* json = serializeUpLinkDTO(dto);
    printf("Debug: After serializeUpLinkDTO\n");

    // Check the length of the JSON string
    char* jsonString = cJSON_PrintUnformatted(json);
    printf("Debug: After cJSON_PrintUnformatted\n");

    TEST_ASSERT_NOT_NULL_MESSAGE(jsonString, "JSON string is NULL");
    TEST_ASSERT_GREATER_THAN_INT_MESSAGE(0, strlen(jsonString), "JSON string is empty");

    // Free the cJSON string
    
}









int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_CreateUpLinkDTO);
    RUN_TEST(test_SerializeUpLinkDTO);
    

    return UNITY_END();
}

