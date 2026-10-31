#include <REGX51.H>
/* Assumption: segment bus P2; digit enables P3.0=tens, P3.1=units; HIGH enables digit. */
sbit TEN=P3^0; sbit UNIT=P3^1;
unsigned char code seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void wait_short(void){ unsigned int i; for(i=0;i<100;i++); }
void display(unsigned char a,unsigned char b){
    TEN=0; UNIT=0; P2=seg[a]; TEN=1; wait_short(); TEN=0;
    P2=seg[b]; UNIT=1; wait_short(); UNIT=0;
}
void main(void){
    unsigned char n; unsigned int k;
    while(1) for(n=0;n<10;n++) for(k=0;k<250;k++) display(0,n);
}
