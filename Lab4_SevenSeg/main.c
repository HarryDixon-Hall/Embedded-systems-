/**
 * @file main.c
 * @brief Main function for Lab4_SevenSeg application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#define REFRESH_MS 2
#define DEBOUNCE_MS 30
#define BLANK_US 80
#define DIG_ACTIVE_HIGH 1 
#define SCAN_ON_US 900
#define PRESS_TICKS 6
#define HOLD_DELAY_TICKS 60 // wait before auto-repeat starts
#define REPEAT_TICKS_SLOW 10 // slow repeat period
#define REPEAT_TICKS_FAST 3 // fast repeat period
#define ACCEL_TICKS 200 // time before fast repeat starts

const unsigned char CC_DIGITS[10] = {
 0x3F, // 0 = a b c d e f
 0x06, // 1 = b c
 0x5B, // 2 = a b d e g
 0x4F, // 3 = a b c d g
 0x66, // 4 = b c f g
 0x6D, // 5 = a c d f g
 0x7D, // 6 = a c d e f g
 0x07, // 7 = a b c
 0x7F, // 8 = a b c d e f g
 0x6F // 9 = a b c d f g
};
const unsigned char DIG_MASKS[4] = {0x01,0x02,0x04,0x08};

unsigned char DIG_MAP[4] = {3,2,1,0};
static unsigned char prev_up =1, prev_dn =1;

unsigned char seg_for(unsigned char d) { return CC_DIGITS[d % 10u]; }

void all_digits_off(void) { RA0_bit = 0; RA1_bit = 0; RA2_bit = 0; RA3_bit = 0; }

unsigned char fell(unsigned char now, unsigned char *prev) {
    unsigned char event = (*prev == 1u && now == 0u);
    *prev = now;
    return event;
}

void enable_digit(unsigned char idx) {
 if (idx == 0u) RA0_bit = 1;
 else if (idx == 1u) RA1_bit = 1;
 else if (idx == 2u) RA2_bit = 1;
 else if (idx == 3u) RA3_bit = 1;
}

unsigned char seg_from_digit(unsigned char d) {
 return CC_DIGITS[d % 10u];
}

void split_digits(unsigned int value, unsigned char *d0, unsigned char *d1,
 unsigned char *d2, unsigned char *d3) {
 *d0 = value % 10u;
 *d1 = (value / 10u) % 10u;
 *d2 = (value / 100u) % 10u;
 *d3 = (value / 1000u) % 10u;
}

void split4(unsigned int v, unsigned char *u, unsigned char *t,
 unsigned char *h, unsigned char *th){
 *u = v % 10u;
 *t = (v/10u) % 10u;
 *h = (v/100u) % 10u;
 *th = (v/1000u) % 10u;
}

unsigned char fell_RB0(void){ unsigned char n=RB0_bit, e=(prev_up==1u && n== 0u); prev_up=n; return e; }
unsigned char fell_RB1(void){ unsigned char n=RB1_bit, e=(prev_dn==1u && n == 0u); prev_dn=n; return e; }

unsigned char pressed_falling_RB0(unsigned char *prev) {
 unsigned char now = RB0_bit;
 if (*prev == 1u && now == 0u) {
 Delay_ms(DEBOUNCE_MS);
 if (RB0_bit == 0u) { *prev = 0u; return 1u; }
 }
 *prev = now;
 return 0u;
}
unsigned char pressed_falling_RB1(unsigned char *prev) {
 unsigned char now = RB1_bit;
 if (*prev == 1u && now == 0u) {
 Delay_ms(DEBOUNCE_MS);
 if (RB1_bit == 0u) { *prev = 0u; return 1u; }
 }
 *prev = now;
 return 0u;
}
void show_digit(unsigned char d) {
 LATD = seg_from_digit(d);
}
void all_off(void){ if (DIG_ACTIVE_HIGH) LATA=0x00; else LATA=0x0F; }

void enable_pos(unsigned char pos){
 unsigned char mask = DIG_MASKS[ DIG_MAP[pos] ];
 if (DIG_ACTIVE_HIGH) LATA = mask; else LATA = (unsigned char)(0x0F ^ mask);
}

int main(void)
{
    // Task 1
    // unsigned char seg;
    // ANSELD = 0x00; ANSELA = 0x00; // digital
    // TRISD = 0x00; // segments out
    // TRISA0_bit = 0; // digit 0 enable out
    // LATA = 0x00; // all digits off
    // seg = CC_DIGITS[3];
    // LATD = seg; // show 3
    // LATA.B0 = 1; // enable digit 0
    // while(1) { }

    //Task 2
    // unsigned char seg;
    // ANSELD = 0x00; ANSELA = 0x00;
    // TRISD = 0x00;
    // TRISA0_bit = 0;
    // LATA = 0x00;
    // seg = CC_DIGITS[0];
    // LATD = seg;
    // LATA.B0 = 1;
    
    // while(1) {
    //     for(int i = 0; i <= 10; ++i){
    //         seg = CC_DIGITS[i];
    //         LATD = seg;
    //         Delay_100ms();
    //     }
    //  }

    // Task 3 
    // unsigned char value = 0;

    // ANSELB = 0x00; ANSELD = 0x00; ANSELA = 0x00;
    // TRISB0_bit = 1; TRISB1_bit = 1;
    // TRISD = 0x00; TRISA0_bit = 0;
    // LATA = 0x00; LATA.B0 = 1;


    // while (1)
    // {

    //     if (fell(RB0_bit, &prev_up)) {
    //         Delay_ms(30);
    //         if (RB0_bit == 0u)
    //             value = (value + 1u) % 10u; 
    //     }

    //     if (fell(RB1_bit, &prev_dn)) { 
    //         Delay_ms(30);
    //         if (RB1_bit == 0u)
    //             value = (value + 9u) % 10u;        
    //     }

    //     LATD = CC_DIGITS[value];
    // }

    // Task 4
    // unsigned char value = 0;
    // unsigned char prev0 = 1, prev1 = 1;
    // ANSELB = 0x00; ANSELD = 0x00; ANSELA = 0x00;
    // TRISB0_bit = 1; TRISB1_bit = 1;
    // TRISD = 0x00; TRISA0_bit = 0;
    // LATA = 0x00; LATA.B0 = 1;
    // show_digit(value);
    // while(1) {
    // if (pressed_falling_RB0(&prev0)) { value = (value + 1u) % 10u; show_digit(value); }
    // if (pressed_falling_RB1(&prev1)) { value = (value + 9u) % 10u; show_digit(value); }
    // }

    //Task 5a ghosting
    // unsigned int value = 0;
    // unsigned char d0, d1, d2, d3;
    // ANSELB=0x00; ANSELD=0x00; ANSELA=0x00;
    // TRISB0_bit=1; TRISB1_bit=1;
    // TRISD=0x00;
    // TRISA0_bit=0; TRISA1_bit=0; TRISA2_bit=0; TRISA3_bit=0;
    // while(1) {
    //     if (fell_RB0()) { Delay_ms(DEBOUNCE_MS); if (RB0_bit == 0u) value = (value + 1u) % 10000u; }
    //     if (fell_RB1()) { Delay_ms(DEBOUNCE_MS); if (RB1_bit == 0u) value = (value + 9999u) % 10000u; }split_digits(value, &d0, &d1, &d2, &d3);
    //     LATD = seg_for(d0); all_digits_off(); enable_digit(0); Delay_ms(REFRESH_MS);
    //     LATD = seg_for(d1); all_digits_off(); enable_digit(1); Delay_ms(REFRESH_MS);
    //     LATD = seg_for(d2); all_digits_off(); enable_digit(2); Delay_ms(REFRESH_MS);
    //     LATD = seg_for(d3); all_digits_off(); enable_digit(3); Delay_ms(REFRESH_MS);
    // }

    // Task 5b
    // unsigned int value = 0;
    // unsigned char d0, d1, d2, d3;
    // ANSELB = 0x00; ANSELD = 0x00; ANSELA = 0x00;
    // TRISB0_bit = 1; TRISB1_bit = 1;
    // TRISD = 0x00;
    // TRISA0_bit = 0; TRISA1_bit = 0; TRISA2_bit = 0; TRISA3_bit = 0;
    // all_digits_off();
    // while(1) {
    //     if (fell_RB0()) { Delay_ms(DEBOUNCE_MS); if (RB0_bit == 0u) value = (value + 1u) % 10000u; }
    //     if (fell_RB1()) { Delay_ms(DEBOUNCE_MS); if (RB1_bit == 0u) value = (value + 9999u) % 10000u; }
    //     split_digits(value, &d0, &d1, &d2, &d3);
    //     all_digits_off(); LATD = seg_for(d0); enable_digit(3); Delay_ms(REFRESH_MS);
    //     all_digits_off(); LATD = seg_for(d1); enable_digit(2); Delay_ms(REFRESH_MS);
    //     all_digits_off(); LATD = seg_for(d2); enable_digit(1); Delay_ms(REFRESH_MS);
    //     all_digits_off(); LATD = seg_for(d3); enable_digit(0); Delay_ms(REFRESH_MS);
    // }

    // task 5c
    // ANSELA=0x00; ANSELD=0x00;
    // TRISD=0x00;
    // TRISA0_bit=0; TRISA1_bit=0; TRISA2_bit=0; TRISA3_bit=0;
    // while(1){
    //     all_off(); LATD=0x00; Delay_us(BLANK_US); LATD=seg_for(1); enable_pos(0); 
    //     Delay_us(SCAN_ON_US);
    //     all_off(); LATD=0x00; Delay_us(BLANK_US); LATD=seg_for(2); enable_pos(1); 
    //     Delay_us(SCAN_ON_US);
    //     all_off(); LATD=0x00; Delay_us(BLANK_US); LATD=seg_for(3); enable_pos(2); 
    //     Delay_us(SCAN_ON_US);
    //     all_off(); LATD=0x00; Delay_us(BLANK_US); LATD=seg_for(4); enable_pos(3); 
    //     Delay_us(SCAN_ON_US);
    // }

    //Task 5D
    // unsigned int value=0;
    // unsigned char u=0,t=0,h=0,th=0;
    // unsigned char pos=0;
    // unsigned char up_ticks=0, dn_ticks=0;
    // unsigned char up_lat=0, dn_lat=0;
    // ANSELA=0x00; ANSELB=0x00; ANSELD=0x00;
    // TRISD=0x00;
    // TRISA0_bit=0; TRISA1_bit=0; TRISA2_bit=0; TRISA3_bit=0;
    // TRISB0_bit=1; TRISB1_bit=1;
    // LATD=0x00; all_off();
    // while(1){
    // if(pos==0u) split4(value,&u,&t,&h,&th);
    // all_off(); LATD=0x00; Delay_us(BLANK_US);
    // if (pos==0u) LATD=seg_for(u);
    // else if (pos==1u) LATD=seg_for(t);
    // else if (pos==2u) LATD=seg_for(h);
    // else LATD=seg_for(th);
    // enable_pos(pos);
    // Delay_us(SCAN_ON_US);
    // all_off(); LATD=0x00; Delay_us(BLANK_US);
    // pos++; if(pos>=4u) pos=0u;
    // // non-blocking debounce for RB0 and RB1, active-low
    // if (!up_lat){
    // if (RB0_bit==0u){
    // if (up_ticks<PRESS_TICKS) up_ticks++;
    // if (up_ticks==PRESS_TICKS){ value=(value+1u)%10000u; up_lat=1u; }
    // } else up_ticks=0u;
    // } else {
    // if (RB0_bit==1u){ up_lat=0u; up_ticks=0u; }
    // }
    // if (!dn_lat){
    // if (RB1_bit==0u){
    // if (dn_ticks<PRESS_TICKS) dn_ticks++;
    // if (dn_ticks==PRESS_TICKS){ value=(value+9999u)%10000u; dn_lat=1u; }
    // } else dn_ticks=0u;
    // } else {
    // if (RB1_bit==1u){ dn_lat=0u; dn_ticks=0u; }
    // }
    // }

    // Task 5E
    unsigned int value = 0;
    unsigned char u=0,t=0,h=0,th=0, pos=0;
    unsigned int up_press=0, up_hold=0, up_repeat=0;
    unsigned int dn_press=0, dn_hold=0, dn_repeat=0;
    unsigned char up_lat=0, dn_lat=0;
    ANSELA=0x00; ANSELB=0x00; ANSELD=0x00;
    TRISD=0x00;
    TRISA0_bit=0; TRISA1_bit=0; TRISA2_bit=0; TRISA3_bit=0;
    TRISB0_bit=1; TRISB1_bit=1;
    LATD=0x00; all_off();
    while(1){
    if (pos==0u) split4(value,&u,&t,&h,&th);
    all_off(); LATD=0x00; Delay_us(BLANK_US);
    if (pos==0u) LATD=seg_for(u);
    else if (pos==1u) LATD=seg_for(t);
    else if (pos==2u) LATD=seg_for(h);
    else LATD=seg_for(th);
    enable_pos(pos);
    Delay_us(SCAN_ON_US);
    all_off(); LATD=0x00; Delay_us(BLANK_US);
    pos++; if (pos>=4u) pos=0u;
    // run button logic once per frame start
    if (pos==0u){
    // UP button with auto-repeat
    if (RB0_bit==0u){
    if (up_press < PRESS_TICKS) up_press++;
    if (up_press == PRESS_TICKS && up_lat==0u){
    value = (value + 1u) % 10000u; up_lat=1u; up_hold=0u; up_repeat=0u;
    } else if (up_lat){
    up_hold++;
    if (up_hold >= HOLD_DELAY_TICKS){
    unsigned int step = (up_hold >= ACCEL_TICKS) ? REPEAT_TICKS_FAST : 
    REPEAT_TICKS_SLOW;
    if (++up_repeat >= step){ value = (value + 1u) % 10000u; up_repeat = 
    0u; }
    }
    }
    } else { up_press=0u; up_hold=0u; up_repeat=0u; up_lat=0u; }
    // DOWN button with auto-repeat
    if (RB1_bit==0u){
    if (dn_press < PRESS_TICKS) dn_press++;
    if (dn_press == PRESS_TICKS && dn_lat==0u){
    value = (value + 9999u) % 10000u; dn_lat=1u; dn_hold=0u; dn_repeat=0u;
    } else if (dn_lat){
    dn_hold++;
    if (dn_hold >= HOLD_DELAY_TICKS){
    unsigned int step = (dn_hold >= ACCEL_TICKS) ? REPEAT_TICKS_FAST : 
    REPEAT_TICKS_SLOW;
    if (++dn_repeat >= step){ value = (value + 9999u) % 10000u; dn_repeat 
    = 0u; }
    }
    }
    } else { dn_press=0u; dn_hold=0u; dn_repeat=0u; dn_lat=0u; }
    }
    }

    return 0;
}
