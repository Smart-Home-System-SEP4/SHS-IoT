//test_display.c

#include "unity.h"
#include "display_module.h"
#include"display.h"


  // Assuming you have a mock implementation for display functions

void setUp(void) {
    // Set up any necessary initialization
    display_init();  // Initialize display for testing
}

void tearDown(void) {
    // Clean up any resources
}

void test_DisplayModuleInitialization(void) {
    // Test display module initialization
    display_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE((PORTG & (1 << PG5)) >> PG5, 1, "LATCH is not set up correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE((PORTH & (1 << PH5)) >> PH5, 1, "DATA is not set up correctly");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE((PORTH & (1 << PH4)) >> PH4, 1, "CLOCK is not set up correctly");

    // Add additional conditions as needed based on your specific requirements
}


void test_DisplayData(void) {
    // Mock or initialize any necessary variables or functions
    // Mock display_setValues function
    display_setValues_Expect(2, 5, 17, 12);  // Expect display_setValues to be called with these arguments
    display_setValues_IgnoreArg_value3();  // Ignore the third argument for simplicity

    // Call the function to display data
    displayData(25, 5, 40);

    // Add assertions based on the expected behavior of display_setValues
    // Check if display_setValues is called with the expected arguments
    // You can use Unity's assertion macros for this
    display_setValues_Verify();  // Verify that display_setValues was called with expected arguments

    // Add additional conditions as needed based on your specific requirements
}

int main(void) {
    UNITY_BEGIN();
     RUN_TEST(test_DisplayModuleInitialization);
    // RUN_TEST(test_DisplayData);
    return UNITY_END();
}
