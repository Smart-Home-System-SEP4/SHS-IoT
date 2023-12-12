// Assuming ServerResponseDAO.c
#include "ServerResponseDAO.h"


// Assuming a global variable to store the server response
char serverResponseJsonString[MAX_RESPONSE_LENGTH];  // Adjust the length accordingly

void ServerResponseDAO_handleData(const char* data) {
    if (data != NULL) {
        // Copy the received data to the global variable
        strncpy(serverResponseJsonString, data, MAX_RESPONSE_LENGTH - 1);
        serverResponseJsonString[MAX_RESPONSE_LENGTH - 1] = '\0';
    }
}
