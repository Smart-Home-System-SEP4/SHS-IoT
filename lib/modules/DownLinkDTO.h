// DownLinkDTO.h
#ifndef DOWNLINKDTO_H
#define DOWNLINKDTO_H

#include "includes.h"
#include "cJSON.h"

#define UID_LENGTH 12

typedef struct {
    char device_UID[UID_LENGTH + 1];
    uint8_t temperature_limit_high;
    uint8_t temperature_limit_low;
    uint8_t humidity_limit_high;
    uint8_t humidity_limit_low;
    uint8_t servo_limit_high;  
    uint8_t servo_normal;
    uint8_t servo_limit_low; 
      
    
    
} DownLinkDTO;
// Function to create a DownLinkDTO
DownLinkDTO* createDownLinkDTO(const char* device_UID, uint8_t temperature_limit_high,uint8_t temperature_limit_low, uint8_t humidity_limit_high,
                               uint8_t humidity_limit_low, uint8_t servo_limit_high, uint8_t servo_normal,
                               uint8_t servo_limit_low);

// Function to serialize a DownLinkDTO to JSON
cJSON* serializeDownLinkDTO(const DownLinkDTO* dto);

// Function to deserialize a DownLinkDTO from JSON
DownLinkDTO* deserializeDownLinkDTO(const cJSON* json);

#endif // DOWNLINKDTO_H
