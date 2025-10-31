#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#define BUZZER LATC2_bit // Buzzer connected to RC2 pin

// Frequencies for notes (in Hz)
const unsigned int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

// Simple mapping for readability
#define NOTE_C4 notes[0]
#define NOTE_D4 notes[1]
#define NOTE_E4 notes[2]
#define NOTE_F4 notes[3]
#define NOTE_G4 notes[4]
#define NOTE_A4 notes[5]
#define NOTE_B4 notes[6]
#define NOTE_C5 notes[7]

// Function to play a tone
void playTone(unsigned int frequency, unsigned int duration_ms) {
    unsigned long period_us;
    unsigned long cycles;
    unsigned int i;

    if (frequency == 0) {
        Delay_ms(1000);
        return;
    }

    period_us = 1000000UL / frequency;
    cycles = (duration_ms * 1000UL) / period_us;

    for (i = 0; i < cycles; i++) {
        BUZZER = 1;
        Delay_us(period_us / 2);
        BUZZER = 0;
        Delay_us(period_us / 2);
    }
}

int main(void) {
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    ANSELC = 0;    // Configure PORTC as digital
    TRISC.RC2 = 0; // Set RC2 as output
    BUZZER = 0;
    Delay_ms(100);

    while (1) {
        // Happy Birthday melody (note, duration_ms)
        playTone(NOTE_C4, 300);
        Delay_ms(50);
        playTone(NOTE_C4, 150);
        Delay_ms(50);
        playTone(NOTE_D4, 500);
        Delay_ms(50);
        playTone(NOTE_C4, 500);
        Delay_ms(50);
        playTone(NOTE_F4, 500);
        Delay_ms(50);
        playTone(NOTE_E4, 800);
        Delay_ms(300);

        playTone(NOTE_C4, 300);
        Delay_ms(50);
        playTone(NOTE_C4, 150);
        Delay_ms(50);
        playTone(NOTE_D4, 500);
        Delay_ms(50);
        playTone(NOTE_C4, 500);
        Delay_ms(50);
        playTone(NOTE_G4, 500);
        Delay_ms(50);
        playTone(NOTE_F4, 800);
        Delay_ms(300);

        playTone(NOTE_C4, 300);
        Delay_ms(50);
        playTone(NOTE_C4, 150);
        Delay_ms(50);
        playTone(NOTE_C5, 500);
        Delay_ms(50);
        playTone(NOTE_A4, 500);
        Delay_ms(50);
        playTone(NOTE_F4, 500);
        Delay_ms(50);
        playTone(NOTE_E4, 500);
        Delay_ms(50);
        playTone(NOTE_D4, 800);
        Delay_ms(300);

        playTone(NOTE_B4, 300);
        Delay_ms(50);
        playTone(NOTE_B4, 150);
        Delay_ms(50);
        playTone(NOTE_A4, 500);
        Delay_ms(50);
        playTone(NOTE_F4, 500);
        Delay_ms(50);
        playTone(NOTE_G4, 500);
        Delay_ms(50);
        playTone(NOTE_F4, 800);

        Delay_ms(2000); // Pause before repeating
    }

    return 0;
}
