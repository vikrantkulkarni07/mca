#include <LPC214x.h>
/* LPC2148 trainer LEDs assumed on P1.24-P1.31; verify polarity. */
#define LED_MASK 0xFF000000
void delay(unsigned int t){ unsigned int i,j; for(i=0;i<t;i++) for(j=0;j<5000;j++); }
int main(void){
    PINSEL2=0; IODIR1|=LED_MASK;
    while(1){ IOSET1=LED_MASK; delay(500); IOCLR1=LED_MASK; delay(500); }
}
