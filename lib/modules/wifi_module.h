// wifi_module.h
#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include "includes.h"
#include "cJSON.h"
#include "wifi.h"
#include "pc_comm.h"
#include <stdlib.h>
#include <stdio.h>


typedef void (*WiFiCallback)(const char* data);

void initPCCommAndWiFi();
void sendDTO_to_WiFi(const cJSON* json);
#endif // WIFI_MODULE_H