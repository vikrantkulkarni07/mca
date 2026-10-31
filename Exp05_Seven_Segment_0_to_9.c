#include <REGX51.H>
/* Common cathode codes; P2 segment bus; bit order dp-g-f-e-d-c-b-a. */
unsigned char code seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void delay(void){ unsigned int i,j; for(i=0;i<200;i++) for(j=0;j<1275;j++); }
void main(void){
    unsigned char i;
    while(1) for(i=0;i<10;i++){ P2=seg[i]; delay(); }
}
