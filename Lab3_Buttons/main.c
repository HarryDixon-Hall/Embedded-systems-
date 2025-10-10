/**
 * @file main.c
 * @brief Main function for Lab3_Buttons application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

unsigned char pressed_falling_debounced(void);

int main(void)
{
    ANSELB = 0;
    ANSELC = 0;
    TRISB0_bit = 1; // RB0 input
    TRISC0_bit = 0; // RC0 output
    LATC0_bit = 0;




    while(1)
    {
        // if(RB0_bit == 1)
        // {
        //     LATC0_bit = 1;
        // }
        // else
        // {
        //     LATC0_bit = 0;
        // }

        // unsigned char current = RB0_bit;
        // if ((previous == 1) && (current == 0))
        // {
        //     LATC0_bit = !LATC0_bit;
        //     Delay_ms(80);
        // }
        // previous = current;

        // unsigned char cur_inc = RB0_bit;
        // unsigned char cur_dec = RB1_bit;

        // if((prev_inc == 1) && (cur_inc == 0))
        // {
        //     counter++;
        //     LATC = counter;
        //     Delay_ms(80);
        // }

        // if(prev_dec == 1 && cur_dec == 0)
        // {
        //     counter--;
        //     LATC = counter;
        //     Delay_ms(80);
        // }

        // prev_inc = cur_inc;
        // prev_dec = cur_dec;

        if (pressed_falling_debounced()) { // call the helper every loop
            LATC0_bit = !LATC0_bit; // toggle LED once per real press
        }
        
    }
    





    return 0;
}

#define BUTTON1 RB0_bit
#define LED1 LATC0_bit

unsigned char pressed_falling_debounced(void) {
    static unsigned char prev = 1; // remember last level between calls
    unsigned char cur = BUTTON1; // read RB0 now
    if (prev == 1 && cur == 0) { // possible falling edge
        Delay_ms(30); // let the contacts settle
        if (BUTTON1 == 0) { // still low, treat as a real press
        prev = 0; // update last level
        return 1; // report a press event
        }
    }
    prev = cur; // no valid press, just update
    return 0; // no event
}