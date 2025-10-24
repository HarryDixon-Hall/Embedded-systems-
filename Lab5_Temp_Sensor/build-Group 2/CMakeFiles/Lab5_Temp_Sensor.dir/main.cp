#line 1 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems/Lab5_Temp_Sensor/main.c"
#line 15 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems/Lab5_Temp_Sensor/main.c"
unsigned int VREF_mV = 5000u;

 const unsigned char CC_DIGITS[10] = {
 0x3F,
 0x06,
 0x5B,
 0x4F,
 0x66,
 0x6D,
 0x7D,
 0x07,
 0x7F,
 0x6F
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
 ANSELE = 0x02;
 TRISE1_bit = 1;
 ADCON1 = 0x00;
 ADCON2 = 0xA9;
}

unsigned int ADC_Get_Sample(unsigned char ch){
 ADCON0 = (unsigned char)(ch << 2);
 ADCON0.F0 = 1;
 Delay_ms(2);
 ADCON0.F1 = 1;
 while(ADCON0.F1){}
 return (unsigned int)((((unsigned int)ADRESH) << 8) | ADRESL);
}

unsigned int adc_to_Celsius(unsigned int adc){
 unsigned long t = (unsigned long)adc;
 t = t * (unsigned long)VREF_mV;
 t = (t + 511ul) / 1023ul;
 t = t / 10ul;
 if(t>9999ul) t=9999ul;
 return (unsigned int)t;
}

unsigned int lm35_read_T100(void){
 unsigned int adc = ADC_Get_Sample(6);
 unsigned long t = (unsigned long)adc * (unsigned long)VREF_mV * 10ul;
 t = (t + 511ul) / 1023ul;
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
    unsigned int buf[ 8 ];
    unsigned long sum=0;
    ANSELA = 0; ANSELB = 0; ANSELD = 0;
    CM1CON0 = 0; CM2CON0 = 0;
    TRISD = 0;
    TRISA0_bit = 0; TRISA1_bit = 0; TRISA2_bit = 0; TRISA3_bit = 0;
    LATD = 0;
    all_off();

    ADC_Init_Custom();
    T100 = lm35_read_T100();

    for(i=0;i< 8 ;i++){ buf[i]=adc_to_T100(ADC_Get_Sample(6)); sum+=buf[i]; }
    T100_avg = (unsigned int)(sum/ 8 );

    while (1)
    {
#line 186 "C:/Users/796324/OneDrive - hull.ac.uk/GitHub/Embedded-systems/Lab5_Temp_Sensor/main.c"
        if(pos==0u){
        if(++frame >=  250 ){
        frame=0;

        sum -= buf[idx];
        T100 = adc_to_T100(ADC_Get_Sample(6));
        buf[idx] = T100;
        sum += T100;

        idx++; if(idx>= 8 ) idx=0;

        T100_avg = (unsigned int)(sum/ 8 );
        }

        split4(T100_avg,&u,&t,&h,&th);
        }


        all_off(); LATD=0; Delay_us( 80 );
        if (pos==0u) LATD = seg_for(u);
        else if (pos==1u) LATD = (unsigned char)(seg_for(t));
        else if (pos==2u) LATD = seg_for(h) | 0x80u;
        else LATD = (th==0u ? 0x00 : seg_for(th));
        enable_pos(pos); Delay_us( 900 );
        all_off(); LATD=0; Delay_us( 80 );
        pos++; if(pos>=4u) pos=0u;
    }

    return 0;
}
