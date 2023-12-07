// UpLinkDTO.h
#ifndef UPLINK_DTO_H
#define UPLINK_DTO_H

#include "includes.h"
#include "cJSON.h"

typedef struct {
    uint8_t temperature_integer;
    uint8_t temperature_decimal;
    uint8_t humidity_integer;
} UpLinkDTO;

// Function declarations
UpLinkDTO* createUpLinkDTO(uint8_t temperature_integer, uint8_t temperature_decimal, 
                           uint8_t humidity_integer);
cJSON* serializeUpLinkDTO(const UpLinkDTO* dto);
UpLinkDTO* deserializeUpLinkDTO(const cJSON* json);

#endif // UPLINK_DTO_H
