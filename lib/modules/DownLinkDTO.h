// DownLinkDTO.h
#ifndef DOWNLINKDTO_H
#define DOWNLINKDTO_H

#include "cJSON.h" // Include the cJSON library header
#include <stdint.h>
#include"includes.h"

#define UID_LENGTH 16 // Define the length of the UID

typedef struct {
    char device_UID[UID_LENGTH];
    uint8_t servo_angle;
    // Additional members for temperature, humidity, and servo limits
    uint8_t temperature_limit_high;
    uint8_t temperature_limit_low;
    uint8_t humidity_limit_high;
    uint8_t humidity_limit_low;
    uint8_t servo_limit_high;
    uint8_t servo_normal;
    uint8_t servo_limit_low;
} DownLinkDTO;

// Function prototypes
DownLinkDTO* createNewDownLinkDTO(const char* device_UID, uint8_t servo_angle);
cJSON* serializeNewDownLinkDTO(const DownLinkDTO* dto);
DownLinkDTO* deserializeNewDownLinkDTO(const cJSON* json);

DownLinkDTO* createDownLinkDTO(const char* device_UID, uint8_t temperature_limit_high,
                               uint8_t temperature_limit_low, uint8_t humidity_limit_high,
                               uint8_t humidity_limit_low, uint8_t servo_limit_high, uint8_t servo_normal,
                               uint8_t servo_limit_low);
cJSON* serializeDownLinkDTO(const DownLinkDTO* dto);
DownLinkDTO* deserializeDownLinkDTO(const cJSON* json);

#endif // DOWNLINKDTO_H