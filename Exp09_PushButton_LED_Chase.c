#include <REGX51.H>
/* Manual mapping: buttons P0.0/P0.1 active LOW; relay P3.6; buzzer P3.7; LEDs P2. */
sbit B1=P0^0; sbit B2=P0^1; sbit RELAY=P3^6; sbit BUZZER=P3^7;
void delay(unsigned int t){ unsigned int i,j; for(i=0;i<t;i++) for(j=0;j<1275;j++); }
void main(void){
    unsigned char i; B1=1; B2=1; P2=0; RELAY=0; BUZZER=0;
    while(1){
        if(B1==0){ RELAY=1; BUZZER=1; for(i=0;i<8;i++){ P2=(1<<i); delay(200); } P2=0; }
        if(B2==0){ RELAY=0; BUZZER=0; for(i=0;i<8;i++){ P2=(0x80>>i); delay(200); } P2=0; }
    }
}
