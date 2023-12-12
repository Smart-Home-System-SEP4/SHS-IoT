// main.c

#include "includes.h"
#include "dht11.h"
#include "display.h"
#include "leds.h"
#include "light.h"
#include "buzzer.h"
#include "buttons.h"
#include "periodic_task.h"
#include "adxl345.h"
#include "hc_sr04.h"
#include "wifi.h"
#include "avr/power.h"
#include "pir.h"
#include "tone.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h> // Include the interrupt header
#include <stdio.h>
#include"dht11_module.h"
#include"operations_module.h"
#include"dht11_module.h"



#include "includes.h"
#include "dht11_module.h"
#include "display.h"
#include "uart.h"  // Ensure you include the UART header file

int main(void) {
    // Enable global interrupts
    sei();

    //initialize Sensors
    initializeSensors();
    
    // Perform Operations in an infinite loop
    while (1) {
        performOperations();
        }

}