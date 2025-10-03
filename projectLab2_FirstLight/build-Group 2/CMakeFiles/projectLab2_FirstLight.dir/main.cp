#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/main.c"
#line 11 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/main.c"
#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/.meproject/setup/Debug/include/core/preinit.h"
#line 51 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/.meproject/setup/Debug/include/core/preinit.h"
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
#line 52 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/.meproject/setup/Debug/include/core/preinit.h"
#line 1 "C:/Users/796324/AppData/Local/MIKROE/NECTOStudio7/packages/compilers/mikroc/pic/mikroc/include/stdbool.h"



typedef char _Bool;
#line 53 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/.meproject/setup/Debug/include/core/preinit.h"
#line 66 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/.meproject/setup/Debug/include/core/preinit.h"
void preinit(void);
#line 12 "C:/Users/796324/OneDrive - hull.ac.uk/MIKROE/Projects/projectLab2_FirstLight/main.c"



void all_on(){LATC = 0xFF;}


void all_off(){LATC = 0x00;}

void shift_left() {
    unsigned char i;





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
