// DownLinkDTO.c
#include "DownLinkDTO.h"
#include "includes.h"


DownLinkDTO* createDownLinkDTO(uint8_t temperature_limit_high,
                               uint8_t temperature_limit_low, uint8_t humidity_limit_high,
                               uint8_t humidity_limit_low, uint8_t servo_limit_high, uint8_t servo_normal,
                               uint8_t servo_limit_low) {
    DownLinkDTO* dto = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));

    if (dto != NULL) {
        // Set temperature, humidity, and servo limits
        dto->temperature_limit_high = temperature_limit_high;
        dto->temperature_limit_low = temperature_limit_low;
        dto->humidity_limit_high = humidity_limit_high;
        dto->humidity_limit_low = humidity_limit_low;
        dto->servo_limit_high = servo_limit_high;
        dto->servo_normal = servo_normal;
        dto->servo_limit_low = servo_limit_low;
    }
    return dto;
}

cJSON* serializeDownLinkDTO(const DownLinkDTO* dto) {
    cJSON* json = cJSON_CreateObject();

    if (json != NULL) {
        cJSON_AddStringToObject(json, "device_UID", dto->device_UID);
        // Add temperature, humidity, and servo limits to JSON
        cJSON_AddItemToObject(json, "temperature_limit_high", cJSON_CreateNumber(dto->temperature_limit_high));
        cJSON_AddItemToObject(json, "temperature_limit_low", cJSON_CreateNumber(dto->temperature_limit_low));
        cJSON_AddItemToObject(json, "humidity_limit_high", cJSON_CreateNumber(dto->humidity_limit_high));
        cJSON_AddItemToObject(json, "humidity_limit_low", cJSON_CreateNumber(dto->humidity_limit_low));
        cJSON_AddItemToObject(json, "servo_limit_high", cJSON_CreateNumber(dto->servo_limit_high));
        cJSON_AddItemToObject(json, "servo_normal", cJSON_CreateNumber(dto->servo_normal));
        cJSON_AddItemToObject(json, "servo_limit_low", cJSON_CreateNumber(dto->servo_limit_low));
    }
    return json;
}

DownLinkDTO* deserializeDownLinkDTO(const cJSON* json) {
    DownLinkDTO* dto = (DownLinkDTO*)malloc(sizeof(DownLinkDTO));

    if (dto != NULL) {
        // Retrieve temperature, humidity, and servo limits
        cJSON* tempLimitHigh = cJSON_GetObjectItemCaseSensitive(json, "temperature_limit_high");
        cJSON* tempLimitLow = cJSON_GetObjectItemCaseSensitive(json, "temperature_limit_low");
        cJSON* humLimitHigh = cJSON_GetObjectItemCaseSensitive(json, "humidity_limit_high");
        cJSON* humLimitLow = cJSON_GetObjectItemCaseSensitive(json, "humidity_limit_low");
        cJSON* servoLimitHigh = cJSON_GetObjectItemCaseSensitive(json, "servo_limit_high");
        cJSON* servoNormal = cJSON_GetObjectItemCaseSensitive(json, "servo_normal");
        cJSON* servoLimitLow = cJSON_GetObjectItemCaseSensitive(json, "servo_limit_low");

        if (cJSON_IsNumber(tempLimitHigh)  &&
            cJSON_IsNumber(tempLimitLow) && cJSON_IsNumber(humLimitHigh)  &&
            cJSON_IsNumber(humLimitLow) && cJSON_IsNumber(servoLimitHigh) && cJSON_IsNumber(servoNormal) &&
            cJSON_IsNumber(servoLimitLow)) {

            // Set temperature, humidity, and servo limits
            dto->temperature_limit_high = tempLimitHigh->valueint;
            dto->temperature_limit_low = tempLimitLow->valueint;
            dto->humidity_limit_high = humLimitHigh->valueint;
            dto->humidity_limit_low = humLimitLow->valueint;
            dto->servo_limit_high = servoLimitHigh->valueint;
            dto->servo_normal = servoNormal->valueint;
            dto->servo_limit_low = servoLimitLow->valueint;
        } else {
            free(dto);
            return NULL; // Return NULL if deserialization fails
        }
    }

    return dto;
}
