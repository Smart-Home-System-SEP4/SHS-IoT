// ServerResponseDAO.c
#include "ServerResponseDAO.h"
#include <string.h>  // Add this include for strncpy

// Define the global variable
char serverResponseJsonString[MAX_RESPONSE_LENGTH];

// Define the function
void ServerResponseDAO_handleData(const char* data) {
    if (data != NULL) {
        // Copy the received data to the global variable
        strncpy(serverResponseJsonString, data, MAX_RESPONSE_LENGTH - 1);
        serverResponseJsonString[MAX_RESPONSE_LENGTH - 1] = '\0';
    }
}
