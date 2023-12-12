//servo_module.h

#ifndef SERVO_MODULE_H
#define SERVO_MODULE_H
#include "DownLinkDTO.h"
#include <stdint.h>


void moveNewAngle(const DownLinkDTO* downLinkDTO);

void moveServoModuleBasedOnConditions(uint8_t temperature_integer, uint8_t humidity_integer, const DownLinkDTO* downLinkDTO);


#endif // SERVO_MODULE_H
