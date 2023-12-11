// uid_constants.c
#include "uid_constants.h"
#include <avr/eeprom.h>
#include "includes.h"

void readDeviceUID(char* uid) {
    eeprom_read_block(uid, (const void*)0, UID_LENGTH);
    uid[UID_LENGTH] = '\0';  // Ensure null termination
}

void initializeDeviceUID(const char* defaultUID) {
    char uid[UID_LENGTH + 1];
    eeprom_read_block(uid, (const void*)0, UID_LENGTH);

    // Check if the UID is not initialized
    if (uid[0] == '\0') {
        strncpy(uid, defaultUID, UID_LENGTH);
        eeprom_write_block(uid, (void*)0, UID_LENGTH);
    }
}
