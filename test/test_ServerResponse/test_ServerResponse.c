// test_ServerResponseDAO.c

#include "unity.h"

//UnDefining the system 'strncpy' before FFF
//(Because the 'strncpy' declaration gave conflicts between FFF mock & system's string.h )
#undef strncpy


#include "../fff.h"

//Defining the system 'strncpy' after FFF
//(This ensures that FFF's strncpy takes precedence during compilation.)
#define strncpy __builtin___strncpy_chk 


#define MAX_RESPONSE_LENGTH 1024

#include "ServerResponseDAO.h"

DEFINE_FFF_GLOBALS;

void setUp(void) {
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

// Mocks
FAKE_VOID_FUNC(strncpy, char*, const char*, size_t);

void test_ServerResponseDAO_handleData(void) {
    // Set up the expected behavior for the mocked function
    const char* testData = "{'key':'value'}";
    const size_t maxResponseLength = MAX_RESPONSE_LENGTH - 1;  // Considering the null terminator

    // Call the function under test
    ServerResponseDAO_handleData(testData);

    // Check the behavior of the function
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE(testData, serverResponseJsonString, maxResponseLength, "Data was not copied correctly");
}

int main(void) {
    UNITY_BEGIN();

    // Run ServerResponseDAO tests
    RUN_TEST(test_ServerResponseDAO_handleData);

    return UNITY_END();
}
