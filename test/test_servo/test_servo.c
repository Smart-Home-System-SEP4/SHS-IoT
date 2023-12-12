#include "unity.h"
#include "../fff.h"
#include "DownLinkDTO.h"
#include"servo_module.h"
#include"servo.h"
#include"tone.h"
DEFINE_FFF_GLOBALS;

// Mock or fake functions
FAKE_VALUE_FUNC0(uint8_t, getServoPosition);
FAKE_VOID_FUNC0(tone_play_windows_xp_error);
FAKE_VOID_FUNC1(moveServoToAngle, uint8_t);

// Function under test
void moveNewAngle(const DownLinkDTO* downLinkDTO);

// Define a fake DownLinkDTO for testing
DownLinkDTO fakeDownLinkDTO;

void setUp(void) {
    // Reset the FFF mock objects and call history before each test
    FFF_RESET_HISTORY();
}

void tearDown(void) {
    // Clean up any resources
}

void test_MoveNewAngle_ServoNotAtAngle_ShouldMoveServo(void) {
    // Arrange
    fakeDownLinkDTO.servo_angle = 90;  // Set the desired servo angle
    getServoPosition_fake.return_val = 45;  // Set the current servo position

    // Act
    moveNewAngle(&fakeDownLinkDTO);

    // Assert
    TEST_ASSERT_EQUAL_INT(1, getServoPosition_fake.call_count);
    TEST_ASSERT_EQUAL_INT(1, moveServoToAngle_fake.call_count);
    TEST_ASSERT_EQUAL_INT(90, moveServoToAngle_fake.arg0_history[0]);
    TEST_ASSERT_EQUAL_INT(1, tone_play_windows_xp_error_fake.call_count);
}



int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_MoveNewAngle_ServoNotAtAngle_ShouldMoveServo);
    

    return UNITY_END();
}