#include <REGX51.H>
/* Manual mapping: relay P3.6, buzzer P3.7, LED P2.0; active HIGH assumed. */
sbit RELAY=P3^6; sbit BUZZER=P3^7; sbit LED=P2^0;
void delay(unsigned int t){ unsigned int i,j; for(i=0;i<t;i++) for(j=0;j<1275;j++); }
void main(void){
    while(1){
        RELAY=1; BUZZER=1; LED=1; delay(1000);
        RELAY=0; BUZZER=0; LED=0; delay(1000);
    }
}
