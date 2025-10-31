#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/main.c"
#line 2 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/main.c"
#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/.meproject/setup/Debug/include/core/preinit.h"
#line 51 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/.meproject/setup/Debug/include/core/preinit.h"
#line 1 "C:/Users/796324/AppData/Local/MIKROE/NECTOStudio7/packages/compilers/mikroc/pic/mikroc/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;


typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 52 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/.meproject/setup/Debug/include/core/preinit.h"
#line 1 "C:/Users/796324/AppData/Local/MIKROE/NECTOStudio7/packages/compilers/mikroc/pic/mikroc/include/stdbool.h"



typedef char _Bool;
#line 53 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/.meproject/setup/Debug/include/core/preinit.h"
#line 66 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/.meproject/setup/Debug/include/core/preinit.h"
void preinit(void);
#line 3 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/main.c"





const unsigned int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
#line 21 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems-/Lab_6_interfacing-on-board-Buzzer/main.c"
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
        LATC2_bit  = 1;
        Delay_us(period_us / 2);
        LATC2_bit  = 0;
        Delay_us(period_us / 2);
    }
}

int main(void) {

    preinit();


    ANSELC = 0;
    TRISC.RC2 = 0;
    LATC2_bit  = 0;
    Delay_ms(100);

    while (1) {

        playTone( notes[0] , 300);
        Delay_ms(50);
        playTone( notes[0] , 150);
        Delay_ms(50);
        playTone( notes[1] , 500);
        Delay_ms(50);
        playTone( notes[0] , 500);
        Delay_ms(50);
        playTone( notes[3] , 500);
        Delay_ms(50);
        playTone( notes[2] , 800);
        Delay_ms(300);

        playTone( notes[0] , 300);
        Delay_ms(50);
        playTone( notes[0] , 150);
        Delay_ms(50);
        playTone( notes[1] , 500);
        Delay_ms(50);
        playTone( notes[0] , 500);
        Delay_ms(50);
        playTone( notes[4] , 500);
        Delay_ms(50);
        playTone( notes[3] , 800);
        Delay_ms(300);

        playTone( notes[0] , 300);
        Delay_ms(50);
        playTone( notes[0] , 150);
        Delay_ms(50);
        playTone( notes[7] , 500);
        Delay_ms(50);
        playTone( notes[5] , 500);
        Delay_ms(50);
        playTone( notes[3] , 500);
        Delay_ms(50);
        playTone( notes[2] , 500);
        Delay_ms(50);
        playTone( notes[1] , 800);
        Delay_ms(300);

        playTone( notes[6] , 300);
        Delay_ms(50);
        playTone( notes[6] , 150);
        Delay_ms(50);
        playTone( notes[5] , 500);
        Delay_ms(50);
        playTone( notes[3] , 500);
        Delay_ms(50);
        playTone( notes[4] , 500);
        Delay_ms(50);
        playTone( notes[3] , 800);

        Delay_ms(2000);
    }

    return 0;
}
