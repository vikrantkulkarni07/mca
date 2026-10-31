#include <REGX51.H>
/* Assumption: segment bus P2; digit enables P3.0=left, P3.1=right; HIGH enables. */
sbit LEFT=P3^0; sbit RIGHT=P3^1;
unsigned char code seg[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
void wait_short(void){ unsigned int i; for(i=0;i<100;i++); }
void display(unsigned char a,unsigned char b){
    LEFT=0; RIGHT=0; P2=seg[a]; LEFT=1; wait_short(); LEFT=0;
    P2=seg[b]; RIGHT=1; wait_short(); RIGHT=0;
}
void main(void){
    unsigned char n; unsigned int k;
    while(1) for(n=10;n<=15;n++) for(k=0;k<250;k++) display(0,n);
}
