// main.c

#include "includes.h"
#include "operations_module.h"
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