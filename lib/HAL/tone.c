#include "tone.h"
#include "includes.h"

#define BUZ_BIT PA1
#define BUZ_DDR DDRA
#define BUZ_PORT PORTA

void tone_init(){
BUZ_DDR|=(1<<BUZ_BIT);
}


void tone_play(uint16_t frequency, uint16_t duration) {


    // Calculate the half-period delay in microseconds
    uint16_t delay_us = 500000 / frequency;

    // Calculate the number of cycles needed for the specified duration
    uint16_t loop = (uint16_t) ((uint32_t) duration * 1000 / (2 * delay_us));



    // Initialize Timer2 in normal mode
    TCCR2A = 0;
    TCCR2B = 0;

    uint8_t prescaler_bits = 0;
    uint16_t prescaler_value = 0;

    // Choose prescaler based on delay
    if (delay_us > 4000) {
        prescaler_bits = (1 << CS22) | (1 << CS21) | (1 << CS20); // 1024
        prescaler_value = 1024;
    } else if (delay_us > 2000) {
        prescaler_bits = (1 << CS22) | (1 << CS21); // 256
        prescaler_value = 256;
    } else if (delay_us > 1000) {
        prescaler_bits = (1 << CS22) | (1 << CS20); // 128
        prescaler_value = 128;
    } else if (delay_us >500) {
        prescaler_bits = (1 << CS22); // 64
        prescaler_value = 64;
    } else if (delay_us >125) {
        prescaler_bits = (1 << CS21)| (1 << CS20); //32
        prescaler_value = 32;
    }
    else
     {
       prescaler_bits = (1 << CS21) ; // 8
        prescaler_value = 8;
     }

    // Set the prescaler
    TCCR2B = prescaler_bits;

    // Calculate the number of timer ticks needed for the specified delay
    uint8_t num_ticks = (F_CPU / 1000000UL) * delay_us / prescaler_value;




    // Generate the tone
    for (uint16_t i = 0; i < loop; i++) {
        // Set PA1 high
        BUZ_PORT |= (1 << BUZ_BIT);
            // Reset the timer counter
    TCNT2 = 0;

    // Wait until the timer counter reaches the required ticks
    while (TCNT2 < num_ticks) {
        // Busy-wait
    }

        // Set PA1 low
        BUZ_PORT &= ~(1 << BUZ_BIT);
            // Reset the timer counter
    TCNT2 = 0;

    // Wait until the timer counter reaches the required ticks
    while (TCNT2 < num_ticks) {
        // Busy-wait
    }
    }

    TCCR2B = 0;
}

void tone_play_starwars(){

    tone_play(392, 500);  // G4 for 500 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(311, 350);  // E♭4 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(311, 350);  // E♭4 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(392, 1000); // G4 for 1000 ms

    tone_play(784, 500);  // G5 for 500 ms
    tone_play(784, 500);  // G5 for 500 ms
    tone_play(784, 500);  // G5 for 500 ms
    tone_play(740, 350);  // F#5 for 350 ms
    tone_play(587, 150);  // D5 for 150 ms
    tone_play(523, 500);  // C5 for 500 ms
    tone_play(466, 350);  // B4 for 350 ms
    tone_play(440, 150);  // A4 for 150 ms
    tone_play(392, 1000); // G4 for 1000 ms
}
void tone_play_windows_xp_startup() {
    // Define the frequency and duration for each note
    uint16_t frequencies[] = {659, 659, 659, 523, 587, 659, 784, 784, 784, 740, 587, 523, 466, 440, 392};
    uint16_t durations[] = {150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 150, 300};

    // Play each note in the melody
    for (size_t i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++) {
        tone_play(frequencies[i], durations[i]);
        _delay_ms(50); // Add a small delay between notes for a more accurate representation
    }
}
void tone_play_windows_xp_error() {
    // Define the frequency and duration for each note
    uint16_t frequencies[] = {784, 659, 523, 659, 784};
    uint16_t durations[] = {100, 100, 100, 100, 300};

    // Play each note in the error sound
    for (size_t i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++) {
        tone_play(frequencies[i], durations[i]);
        _delay_ms(50); // Add a small delay between notes for a more accurate representation
    }
}