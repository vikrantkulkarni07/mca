#include <LPC214x.h>
/* Eight LEDs assumed on P1.24-P1.31; four upper bits ON, four lower bits OFF. */
#define LED_MASK 0xFF000000
int main(void){
    PINSEL2=0; IODIR1|=LED_MASK;
    IOCLR1=LED_MASK;
    IOSET1=0xF0000000;
    while(1);
}
