//wifi_module.c

#include <avr/eeprom.h>
#include "includes.h"
#include "wifi_module.h"
#include "wifi.h"
#include "pc_comm.h"
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"


static WiFiCallback wifiCallback = NULL;

void initPCCommAndWiFi() {
    pc_comm_init(9600, NULL);
    wifi_init();
    
    wifi_command_join_AP("LOST CuB", "Denmark2022");
    wifi_command_create_TCP_connection("192.168.78.179", 23, NULL, NULL);
}


void sendDTO_to_WiFi(const cJSON* json) {
    if (json != NULL) {
        char* buffer = cJSON_Print(json);

        // Check if callback is set and call it
        if (wifiCallback != NULL) {
            wifiCallback(buffer);
        }

        if (buffer != NULL) {
            // Enclose cJSON output in square brackets and add newlines
            uint8_t* wrappedBuffer = (uint8_t*)malloc(strlen(buffer) + 10); // +8 for '[\n', '\n', ']' and '\0'
            if (wrappedBuffer != NULL) {
                sprintf(wrappedBuffer, "\n\n%s\n\n", buffer);

                // Transmit the wrapped buffer
                wifi_command_TCP_transmit(wrappedBuffer, strlen(wrappedBuffer));
                pc_comm_send_string_blocking(wrappedBuffer);

                // Free the buffers after transmission
                free(wrappedBuffer);
            } else {
                fprintf(stderr, "Error: Memory allocation failed\n");
            }

            free(buffer);  // Free the cJSON output buffer
        } else {
            // Handle cJSON_Print failure
            fprintf(stderr, "Error: cJSON_Print failed\n");
        }
    } else {
        // Handle NULL cJSON object
        fprintf(stderr, "Error: cJSON object is NULL\n");
    }
}


// Callback function for handling received data
void wifiDataCallback(const char* data) {
    if (data != NULL) {
        // Check if callback is set and call it with the received data
        if (wifiCallback != NULL) {
            wifiCallback(data);
        }

        // Example: Check the received data and perform actions accordingly
        if (strcmp(data, "1") == 0) {
            printf("Received message: We received something!\n");
            // You can add more logic based on the received data
        }
        // Add more conditions as needed
    }
}