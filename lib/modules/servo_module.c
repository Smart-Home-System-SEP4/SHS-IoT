// servo_module.c
#include "includes.h"
#include "servo_module.h"
#include "servo.h"
#include "DownLinkDTO.h"



int n = 40; // Set the value of n to the desired number of calls

void moveServoModuleBasedOnConditions(uint8_t temperature_integer, uint8_t humidity_integer, const DownLinkDTO* downLinkDTO) {
    // Get the current servo position
    uint8_t currentServoPosition = getServoPosition();

    // Check if DownLinkDTO is initialized
    if (downLinkDTO != NULL) {
        // Extract values from DownLinkDTO
        uint8_t temperatureLimitHigh = downLinkDTO->temperature_limit_high;
        uint8_t temperatureLimitLow = downLinkDTO->temperature_limit_low;
        uint8_t humidityLimitHigh = downLinkDTO->humidity_limit_high;
        uint8_t humidityLimitLow = downLinkDTO->humidity_limit_low;
        uint8_t servoLimitHigh = downLinkDTO->servo_limit_high;  
        uint8_t servoNormal = downLinkDTO->servo_normal;
        uint8_t servoLimitLow = downLinkDTO->servo_limit_low;   

        // Check conditions and move servo accordingly
        if (temperature_integer > temperatureLimitHigh && humidity_integer > humidityLimitHigh) {
            // Move servo to servoLimitHigh degrees if not already there
            if (currentServoPosition != servoLimitHigh) {
                
                moveServoToAngle(servoLimitHigh);
            }
        } else if (temperature_integer < temperatureLimitLow && humidity_integer < humidityLimitLow) {
            // Move servo to servoLimitLow degrees if not already there
            if (currentServoPosition != servoLimitLow) {
               
                moveServoToAngle(servoLimitLow);
            }
        } else {
            // Move servo to 0 degrees if not already there
            if (currentServoPosition != servoNormal) {
               
                moveServoToAngle(servoNormal);
            }
        }
    }
}
