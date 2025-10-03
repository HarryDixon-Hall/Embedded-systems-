/**
 * @file main.c
 * @brief Main function for projectLab2_FirstLight application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// set all bits to 1
void all_on(){LATC = 0xFF;}

// set all bits to 0
void all_off(){LATC = 0x00;}

void shift_left() {
    unsigned char i;

    // Left shift bits
    // 00000001
    // Left shift 1 ( 1 << 0b00000001)
    // 00000010
    for(i = 0; i < 8; ++i){ 
        LATC = (1 << i);
        Delay_100ms();
    }
}

void shift_right(){
    unsigned char i;
    for(i = 7; i > 0; --i) {
        LATC = (1 << i);
        Delay_100ms();
    }
}

int main(void)
{
    TRISC = 0x00;
    LATC = 0x01;
    while (1) {
        shift_left();
        Delay_100ms();
        shift_right();
        Delay_100ms();
    }
}
