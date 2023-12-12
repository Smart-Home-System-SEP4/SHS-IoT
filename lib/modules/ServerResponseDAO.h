// Assuming ServerResponseDAO.h
#ifndef SERVER_RESPONSE_DAO_H
#define SERVER_RESPONSE_DAO_H
#define MAX_RESPONSE_LENGTH 256  // Adjust the length accordingly

#include "DownLinkDTO.h"
#include "cJSON.h"
void ServerResponseDAO_handleData(const char* data);

#endif  // SERVER_RESPONSE_DAO_H
