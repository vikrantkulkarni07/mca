/*
 * GLCD drawing template. The LPC2148 manual identifies GLCD data D0-D7
 * on P1.16-P1.23. Control-pin mapping/driver must be taken from the
 * exact Micro-A748 trainer board diagram. This is NOT a complete flash-ready
 * program until GLCD_Init, GLCD_SetPage and GLCD_WriteData are implemented.
 */
#include <LPC214x.h>
unsigned char smiley[8]={0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
void GLCD_Init(void);
void GLCD_SetPage(unsigned char page);
void GLCD_WriteData(unsigned char data);
int main(void){
    unsigned int i;
    GLCD_Init(); GLCD_SetPage(0);
    for(i=0;i<8;i++) GLCD_WriteData(smiley[i]);
    while(1);
}
