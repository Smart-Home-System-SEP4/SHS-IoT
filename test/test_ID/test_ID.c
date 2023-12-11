#include "unity.h"
#include "uid_constants.h"
#include "includes.h"
#include "../fff.h"

DEFINE_FFF_GLOBALS;

// Mocks
FAKE_VOID_FUNC(readDeviceUID, char*);
FAKE_VOID_FUNC(initializeDeviceUID, const char*);
FAKE_VOID_FUNC(eeprom_write_block, const void*, void*, size_t);
FAKE_VOID_FUNC(eeprom_read_block, void*, const void*, size_t);
FAKE_VOID_FUNC(eeprom_clear);

// ...

void setUp(void) {
    // Initialize FFF
    FFF_RESET_HISTORY();
}

void tearDown(void) {
    // Clean up any resources
}

void test_InitializeDeviceUID(void) {
    // Arrange
    char uid[UID_LENGTH + 1];

    // Clean the entire EEPROM before initializing the UID
    eeprom_write_block("", (void*)0, UID_LENGTH + 1);

    // Act
    const char* defaultUID = "DEFAULT123";
    initializeDeviceUID(defaultUID);

    // Assert
    TEST_ASSERT_EQUAL_INT(1, initializeDeviceUID_fake.call_count);
    TEST_ASSERT_EQUAL_STRING(defaultUID, initializeDeviceUID_fake.arg0_history[0]);
    
    // Add more assertions if needed for initialization
}

void test_ReadDeviceUID(void) {
    // Arrange
    const char* defaultUID = "DefaultUID";
    initializeDeviceUID(defaultUID);

    // Act
    char uid[UID_LENGTH + 1];
    readDeviceUID(uid);

    // Assert
    TEST_ASSERT_EQUAL_INT(1, readDeviceUID_fake.call_count);

    // Read the actual value from EEPROM to compare
    char actualUID[UID_LENGTH + 1];
    eeprom_read_block(actualUID, (const void*)0, UID_LENGTH);
    TEST_ASSERT_EQUAL_STRING(actualUID, uid);
}



int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_InitializeDeviceUID);
    RUN_TEST(test_ReadDeviceUID);

    return UNITY_END();
}
