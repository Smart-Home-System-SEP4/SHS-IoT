// UpLinkDTO.c
#include "UpLinkDTO.h"
#include "includes.h"
#include <avr/eeprom.h>

#include "cJSON.h"

UpLinkDTO* createUpLinkDTO(uint8_t temperature_integer, uint8_t temperature_decimal,
                           uint8_t humidity_integer) {
    UpLinkDTO* dto = (UpLinkDTO*)malloc(sizeof(UpLinkDTO));

    if (dto != NULL) {
        dto->temperature_integer = temperature_integer;
        dto->temperature_decimal = temperature_decimal;
        dto->humidity_integer = humidity_integer;
    }

    return dto;
}

cJSON* serializeUpLinkDTO(const UpLinkDTO* dto) {
    cJSON* json = cJSON_CreateObject();

    if (json != NULL) {
        cJSON_AddItemToObject(json, "temperature_integer", cJSON_CreateNumber(dto->temperature_integer));
        cJSON_AddItemToObject(json, "temperature_decimal", cJSON_CreateNumber(dto->temperature_decimal));
        cJSON_AddItemToObject(json, "humidity_percentage", cJSON_CreateNumber(dto->humidity_integer));       
    }

    return json;
}