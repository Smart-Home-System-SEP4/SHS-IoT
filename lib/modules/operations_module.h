// operations_module.h
#ifndef OPERATIONS_MODULE_H
#define OPERATIONS_MODULE_H

#include "includes.h"
#include"DownLinkDTO.h"
#include "servo_module.h"
#include "UpLinkDTO.h"
#include "DownLinkDTO.h"
#include "cJSON.h"
#include "dht11_module.h"
#include "display_module.h"
#include "wifi_module.h"
#include "uid_constants.h"
#include "ServerResponseDAO.h"
#include <stdio.h>
#include "tone.h"



void initializeSensors();
void performOperations();
DownLinkDTO* getTestDownLinkDTO();
#endif // OPERATIONS_MODULE_H
