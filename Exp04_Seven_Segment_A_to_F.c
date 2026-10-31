#include <REGX51.H>
/* Common cathode codes; P2 segment bus; bit order dp-g-f-e-d-c-b-a. */
unsigned char code seg[6]={0x77,0x7C,0x39,0x5E,0x79,0x71}; /* A,b,C,d,E,F */
void delay(void){ unsigned int i,j; for(i=0;i<200;i++) for(j=0;j<1275;j++); }
void main(void){
    unsigned char i;
    while(1) for(i=0;i<6;i++){ P2=seg[i]; delay(); }
}
