#include "unity.h"
#include "uid_constants.h"
#include "includes.h"
#include <string.h>
#include <avr/eeprom.h>

void setUp(void) {
    // Set up any necessary initialization
}

void tearDown(void) {
    // Clean up any resources
}

void test_ReadDeviceUID(void) {
    // Arrange
    char uid[UID_LENGTH + 1];

    // Clean the entire EEPROM before writing the test UID
    eeprom_write_block("", (void*)0, UID_LENGTH);

    // Initialize EEPROM with a known UID
    const char* testUID = "TEST1234";
    eeprom_write_block(testUID, (void*)0, UID_LENGTH);

    // Act
    readDeviceUID(uid);

    // Assert
    TEST_ASSERT_EQUAL_STRING_MESSAGE(testUID, uid, "Read UID does not match the initialized UID");
    // Add additional conditions if needed
}

void test_InitializeDeviceUID(void) {
    // Arrange
    char uid[UID_LENGTH + 1];

    // Clean the entire EEPROM before initializing the UID
    eeprom_write_block("", (void*)0, UID_LENGTH);

    // Act
    const char* defaultUID = "DEFAULT123";
    initializeDeviceUID(defaultUID);

    // Read the initialized UID from EEPROM
    readDeviceUID(uid, (const void*)0, UID_LENGTH);

    // Debugging: Print actual initialized UID for debugging
    printf("Actual Initialized UID: %s\n", uid);

    // Assert
    TEST_ASSERT_EQUAL_STRING_MESSAGE(defaultUID, uid, "Initialized UID does not match the default UID");
    // Add additional conditions if needed
}

int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_ReadDeviceUID);
    RUN_TEST(test_InitializeDeviceUID);

    return UNITY_END();
}
