#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/main.c"
#line 11 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/main.c"
#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/.meproject/setup/Debug/include/core/preinit.h"
#line 51 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/.meproject/setup/Debug/include/core/preinit.h"
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
#line 52 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/.meproject/setup/Debug/include/core/preinit.h"
#line 1 "C:/Users/796324/AppData/Local/MIKROE/NECTOStudio7/packages/compilers/mikroc/pic/mikroc/include/stdbool.h"



typedef char _Bool;
#line 53 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/.meproject/setup/Debug/include/core/preinit.h"
#line 66 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/.meproject/setup/Debug/include/core/preinit.h"
void preinit(void);
#line 12 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/main.c"


unsigned char pressed_falling_debounced(void);

int main(void)
{
    ANSELB = 0;
    ANSELC = 0;
    TRISB0_bit = 1;
    TRISC0_bit = 0;
    LATC0_bit = 0;




    while(1)
    {
#line 66 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/Lab3_Buttons/main.c"
        if (pressed_falling_debounced()) {
            LATC0_bit = !LATC0_bit;
        }

    }






    return 0;
}

unsigned char pressed_falling_debounced(void) {
    static unsigned char prev = 1;
    unsigned char cur = RB0_bit;
    if (prev == 1 && cur == 0) {
        Delay_ms(30);
        if (RB0_bit == 0) {
        prev = 0;
        return 1;
        }
    }
    prev = cur;
    return 0;
}
