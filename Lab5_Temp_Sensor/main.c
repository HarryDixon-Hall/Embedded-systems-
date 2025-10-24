/**
 * @file main.c
 * @brief Main function for Lab5_Temp_Sensor application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */

#define SCAN_ON_US 900
#define BLANK_US 80
#define SAMPLE_FRAMES 250 
#define MA_N 8 
unsigned int VREF_mV = 5000u;

 const unsigned char CC_DIGITS[10] = {
 0x3F, // 0
 0x06, // 1
 0x5B, // 2
 0x4F, // 3
 0x66, // 4
 0x6D, // 5
 0x7D, // 6
 0x07, // 7
 0x7F, // 8
 0x6F // 9
};

void all_off(){
    LATA = 0x00;
}

void enable_pos(unsigned char pos){
    LATA = (unsigned char) (1u << pos);
}

unsigned char seg_for(unsigned char d){
 static const unsigned char CC[10] = {
 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
 };
 return CC[d % 10u];
}

void split4(unsigned int v, unsigned char *u, unsigned char *t,
 unsigned char *h, unsigned char *th){
 *u = v % 10u;
 *t = (v / 10u) % 10u;
 *h = (v / 100u) % 10u;
 *th = (v / 1000u)% 10u;
}

void ADC_Init_Custom(void){
 ANSELE = 0x02; // bit1=1 makes RE1 analog (AN6)
 TRISE1_bit = 1; // RE1 as input
 ADCON1 = 0x00; // Vref+ = VDD, Vref- = VSS (ties ADC scale to J5)
 ADCON2 = 0xA9; // right-justified result; safe acquisition and ADC clock
}

unsigned int ADC_Get_Sample(unsigned char ch){
 ADCON0 = (unsigned char)(ch << 2); // select channel in CHS bits
 ADCON0.F0 = 1; // ADON = 1 turns the ADC on
 Delay_ms(2); // let the sample-and-hold capacitor charge
 ADCON0.F1 = 1; // GO/DONE = 1 starts conversion
 while(ADCON0.F1){} // wait until GO/DONE returns to 0
 return (unsigned int)((((unsigned int)ADRESH) << 8) | ADRESL); // 10-bit value
}

unsigned int adc_to_Celsius(unsigned int adc){
 unsigned long t = (unsigned long)adc; // widen to prevent overflow
 t = t * (unsigned long)VREF_mV; // adc * Vref_mV gives microvolts/step-scaled value
 t = (t + 511ul) / 1023ul; // divide by 1023 with rounding gives mV at the pin
 t = t / 10ul; // LM35 is 10 mV per degree => degrees C
 if(t>9999ul) t=9999ul;
 return (unsigned int)t;
}

unsigned int lm35_read_T100(void){
 unsigned int adc = ADC_Get_Sample(6);
 unsigned long t = (unsigned long)adc * (unsigned long)VREF_mV * 10ul; // adc * mV * 10
 t = (t + 511ul) / 1023ul; // rounded divide
 if(t>9999ul) t=9999ul;
 return (unsigned int)t;
}

unsigned int adc_to_T100(unsigned int adc){
 unsigned long t = (unsigned long)adc * (unsigned long)VREF_mV * 10ul;
 t = (t + 511ul) / 1023ul;
 if(t>9999ul) t=9999ul;
 return (unsigned int)t;
}

int main(void)
{
    unsigned char pos=0,th=0, h=0, t=0, u=0,i=0,idx=0;
    unsigned int adc=0,tempC=0;
    unsigned int T100=0, frame=0,T100_avg=0;
    unsigned int buf[MA_N]; // ring buffer holding last N T100 readings
    unsigned long sum=0; // running sum for O(1) average
    ANSELA = 0; ANSELB = 0; ANSELD = 0;
    CM1CON0 = 0; CM2CON0 = 0;
    TRISD = 0;
    TRISA0_bit = 0; TRISA1_bit = 0; TRISA2_bit = 0; TRISA3_bit = 0;
    LATD = 0; 
    all_off(); 

    ADC_Init_Custom(); // enable AN6 on RE1
    T100 = lm35_read_T100(); // first sample at startup

    for(i=0;i<MA_N;i++){ buf[i]=adc_to_T100(ADC_Get_Sample(6)); sum+=buf[i]; }
    T100_avg = (unsigned int)(sum/MA_N);

    while (1)
    {
        //Task 1: scanner sanity check ? show 12.34 on the 4-digit seven-seg
        // all_off(); LATD = 0; Delay_ms(BLANK_US);

        // if (pos==0u) LATD = seg_for(u); // units
        // else if (pos==1u) LATD = (unsigned char)(seg_for(t) | 0x80u); // tens with decimal point (RD7 bit)
        // else if (pos==2u) LATD = seg_for(h); // hundreds
        // else LATD = seg_for(th);

        // enable_pos(pos);
        // Delay_us(SCAN_ON_US);

        // all_off(); LATD = 0; Delay_us(BLANK_US);
        // pos++; if(pos>=4u) pos=0u;


        //Task 2: show raw ADC result (0..1023) from LM35 on AN6 (RE1)
        // if(pos==0u){
        //     adc = ADC_Get_Sample(6); // read AN6 = RE1
        //     if(adc>9999u) adc=9999u; // clamp so it fits 4 digits
        //     split4(adc,&u,&t,&h,&th);
        // }
        //     all_off();LATD=0;Delay_ms(BLANK_US);
        //     if (pos==0u) LATD=seg_for(u);
        //     else if (pos==1u) LATD=seg_for(t);
        //     else if (pos==2u) LATD=seg_for(h);
        //     else LATD=seg_for(th);
        //     enable_pos(pos); Delay_ms(SCAN_ON_US);
        //     all_off(); LATD=0; Delay_ms(BLANK_US);

        //     pos++; if(pos>=4u) pos=0u;


        //Task 3: convert adc to whole degrees Celsius (no decimal point yet)
        // if(pos==0u){
        // adc = ADC_Get_Sample(6);
        // tempC = adc_to_Celsius(adc);
        // split4(tempC,&u,&t,&h,&th); 
        // }
        // all_off(); LATD=0; Delay_us(BLANK_US);
        // if (pos==0u) LATD=seg_for(u);
        // else if (pos==1u) LATD=seg_for(t);
        // else if (pos==2u) LATD = ((th==0u && h==0u) ? 0x00 : seg_for(h));
        // else LATD = (th==0u ? 0x00 : seg_for(th));

        // enable_pos(pos); Delay_us(SCAN_ON_US);
        // all_off(); LATD=0; Delay_us(BLANK_US);

        // pos++; if(pos>=4u) pos=0u;
        

        //Task 4: display two decimals as XX.XX using integer T100 (°C × 100)
        // if(pos==0u){
        // if(++frame >= SAMPLE_FRAMES){ frame=0; T100 = lm35_read_T100(); }
        // split4(T100,&u,&t,&h,&th);
        // }

        //  // Place the decimal point after the tens digit to form XX.XX
        // all_off(); LATD=0; Delay_us(BLANK_US);
        
        // if (pos==0u) LATD = seg_for(u); // units of 0.01°C
        // else if (pos==1u) LATD = (unsigned char)(seg_for(t)); // tens with dp set
        // else if (pos==2u) LATD = seg_for(h) | 0x80u;
        // else LATD = (th==0u ? 0x00 : seg_for(th)); // optional blank leading zero

        // enable_pos(pos); Delay_us(SCAN_ON_US);
        // all_off(); LATD=0; Delay_us(BLANK_US);
        
        // pos++; if(pos>=4u) pos=0u;


        //Task 5: smooth the temperature with a moving average over the last N samples
        if(pos==0u){
        if(++frame >= SAMPLE_FRAMES){
        frame=0;
        // Remove the oldest sample, add a new one
        sum -= buf[idx];
        T100 = adc_to_T100(ADC_Get_Sample(6));
        buf[idx] = T100;
        sum += T100;
        // Advance the index in a ring
        idx++; if(idx>=MA_N) idx=0;
        // Compute the average
        T100_avg = (unsigned int)(sum/MA_N);
        }
        // Split the averaged value into 4 digits
        split4(T100_avg,&u,&t,&h,&th);
        }
        
        // Show XX.XX by adding dp on the tens digit
        all_off(); LATD=0; Delay_us(BLANK_US);
        if (pos==0u) LATD = seg_for(u);
        else if (pos==1u) LATD = (unsigned char)(seg_for(t)); // dp at this position
        else if (pos==2u) LATD = seg_for(h) | 0x80u;
        else LATD = (th==0u ? 0x00 : seg_for(th));
        enable_pos(pos); Delay_us(SCAN_ON_US);
        all_off(); LATD=0; Delay_us(BLANK_US);
        pos++; if(pos>=4u) pos=0u;
    }

    return 0;
}
