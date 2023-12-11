//test_display

#include "unity.h"
#include "../fff.h"  // Adjust the path accordingly
#include "display_module.h"
#include "display.h"
#include <stdint.h>

DEFINE_FFF_GLOBALS;  // Define FFF globals

// Mocks
FAKE_VOID_FUNC(display_init);
FAKE_VOID_FUNC(display_setValues, uint8_t, uint8_t, uint8_t, uint8_t);

void setUp(void) {
    FFF_RESET_HISTORY();  // Reset the history of function calls for FFF
    display_init();
}

void tearDown(void) {
}

void test_DisplayModuleInitialization(void) {
    // Test display module initialization
    display_init();
    // Add additional conditions as needed based on your specific requirements
}

void test_DisplayData(void) {
    // Reset the call count and history before calling displayData
    display_setValues_fake.call_count = 0;

    // Call the function to display data
    displayData(25, 5, 40);

    // Check if display_setValues is called the expected number of times
    TEST_ASSERT_EQUAL_INT(3, display_setValues_fake.call_count);

    // Verify the first call to display_setValues
    int expected_temp_tens = 2;  // Assuming the tens digit of temperature
    int expected_temp_ones = 5;  // Assuming the ones digit of temperature
    int expected_humidity = 40;

    TEST_ASSERT_EQUAL_INT(expected_temp_tens, display_setValues_fake.arg0_history[0]);
    TEST_ASSERT_EQUAL_INT(expected_temp_ones, display_setValues_fake.arg1_history[0]);
    TEST_ASSERT_EQUAL_INT(17, display_setValues_fake.arg2_history[0]);  // Assuming constant value for argument 2
    TEST_ASSERT_EQUAL_INT(12, display_setValues_fake.arg3_history[0]);  // Assuming constant value for argument 3
}

int main(void) {
    UNITY_BEGIN();

    // Run display module tests
    RUN_TEST(test_DisplayModuleInitialization);
    RUN_TEST(test_DisplayData);

    return UNITY_END();
}