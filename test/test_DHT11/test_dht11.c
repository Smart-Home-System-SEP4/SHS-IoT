//test_dht11.c

#include "unity.h"
#include "dht11_module.h"
#include "dht11.h"
#include "includes.h"

void setUp(void) {
    // Set up any necessary test fixtures
}

void tearDown(void) {
    // Clean up after the test
}

void test_DHT11ModuleInitialization(void) {
    // Test DHT11 module initialization
    dht11_init();

    // Check if VCC is set correctly after initialization
    TEST_ASSERT_EQUAL_UINT8_MESSAGE((PORTD & (1 << PD0)) >> PD0, 1, "VCC is not set up correctly");

    // Check if GND is cleared correctly after initialization
    TEST_ASSERT_EQUAL_UINT8_MESSAGE((PORTD & (1 << PD2)) >> PD2, 0, "GND is not set up correctly");

    // Add additional conditions as needed based on your specific requirements
}

void test_ReadDHT11DataWithRetry(void) {
    // Test data reading with retries
    uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;
    TEST_ASSERT_TRUE(readDHT11DataWithRetry(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal));

    // Check if obtained data is within a valid range
    TEST_ASSERT_TRUE_MESSAGE(humidity_integer <= 100 && temperature_integer >= -20 && temperature_integer <= 60, "Data is not within a valid range");

    // Add additional conditions as needed based on your specific requirements
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_DHT11ModuleInitialization);
    RUN_TEST(test_ReadDHT11DataWithRetry);

    return UNITY_END();
}
