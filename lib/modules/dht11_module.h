// dHT11_module.h

#ifndef DHT11_MODULE_H
#define DHT11_MODULE_H

#include "includes.h"

int readDHT11DataWithRetry(uint8_t *humidity_integer, uint8_t *humidity_decimal, uint8_t *temperature_integer, uint8_t *temperature_decimal);

#endif // DHT11_MODULE_H