// UpLinkDTO.c
#include "UpLinkDTO.h"
<<<<<<< HEAD
=======
#include "includes.h"
#include "uid_constants.h"

>>>>>>> 5d90f8922071045b5b1d7cb5f61f1a73e2607635


UpLinkDTO* createUpLinkDTO(uint8_t temperature_integer, uint8_t temperature_decimal,
                           uint8_t humidity_integer, const char* device_UID) {
    UpLinkDTO* dto = (UpLinkDTO*)malloc(sizeof(UpLinkDTO));

    if (dto != NULL) {
        // Copy UID to the DTO
        strncpy(dto->device_UID, device_UID, UID_LENGTH);
        dto->device_UID[UID_LENGTH] = '\0';  // Ensure null termination
        dto->temperature_integer = temperature_integer;
        dto->temperature_decimal = temperature_decimal;
        dto->humidity_integer = humidity_integer;
    }

    return dto;
}

cJSON* serializeUpLinkDTO(const UpLinkDTO* dto) {
    cJSON* json = cJSON_CreateObject();

    if (json != NULL) {
        cJSON_AddStringToObject(json, "device_UID", dto->device_UID);  // Add UID to the JSON
        cJSON_AddItemToObject(json, "temperature_integer", cJSON_CreateNumber(dto->temperature_integer));
        cJSON_AddItemToObject(json, "temperature_decimal", cJSON_CreateNumber(dto->temperature_decimal));
        cJSON_AddItemToObject(json, "humidity_percentage", cJSON_CreateNumber(dto->humidity_integer));       
    }

    return json;
}

// UpLinkDTO* deserializeUpLinkDTO(const cJSON* json) {
//     UpLinkDTO* dto = (UpLinkDTO*)malloc(sizeof(UpLinkDTO));

//     if (dto != NULL) {
//         cJSON* uid = cJSON_GetObjectItemCaseSensitive(json, "device_UID");
//         cJSON* tempInt = cJSON_GetObjectItemCaseSensitive(json, "temperature_integer");
//         cJSON* tempDec = cJSON_GetObjectItemCaseSensitive(json, "temperature_decimal");
//         cJSON* humInt = cJSON_GetObjectItemCaseSensitive(json, "humidity_percentage");
        

//         if (cJSON_IsNumber(tempInt) && cJSON_IsNumber(tempDec) && cJSON_IsNumber(humInt) && cJSON_IsString(uid)) {
           
//             strncpy(dto->device_UID, uid->valuestring, UID_LENGTH);
//             dto->device_UID[UID_LENGTH] = '\0';  // Ensure null termination

//             dto->temperature_integer = tempInt->valueint;
//             dto->temperature_decimal = tempDec->valueint;
//             dto->humidity_integer = humInt->valueint;
            
//         } else {
//             free(dto);
//             return NULL; // Return NULL if deserialization fails
//         }
//     }

//     return dto;
// }
