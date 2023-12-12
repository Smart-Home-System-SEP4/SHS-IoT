// uid_constants.c
#include "uid_constants.h"

<<<<<<< HEAD
=======
#include "includes.h"
>>>>>>> 5d90f8922071045b5b1d7cb5f61f1a73e2607635

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
