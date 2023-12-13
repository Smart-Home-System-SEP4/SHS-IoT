// ServerResponseDAO.h
#ifndef SERVER_RESPONSE_DAO_H
#define SERVER_RESPONSE_DAO_H
#define MAX_RESPONSE_LENGTH 256

#include "DownLinkDTO.h"
#include "cJSON.h"

// Declare the function and the global variable
void ServerResponseDAO_handleData(const char* data);
extern char serverResponseJsonString[MAX_RESPONSE_LENGTH];

#endif  // SERVER_RESPONSE_DAO_H
