#include <REGX51.H>
/* Manual LCD wiring: data P1; EN=P2.0, RW=P2.1, RS=P2.2. */
sbit EN=P2^0; sbit RW=P2^1; sbit RS=P2^2;
void delay(void){ unsigned int i,j; for(i=0;i<50;i++) for(j=0;j<1275;j++); }
void cmd(unsigned char x){ P1=x; RS=0; RW=0; EN=1; delay(); EN=0; delay(); }
void dat(unsigned char x){ P1=x; RS=1; RW=0; EN=1; delay(); EN=0; delay(); }
void init_lcd(void){ cmd(0x38); cmd(0x0C); cmd(0x06); cmd(0x01); }
void main(void){
    unsigned char i; unsigned char msg[]="MCA PRACTICAL";
    init_lcd(); cmd(0xC0);
    for(i=0;msg[i]!='\0';i++) dat(msg[i]);
    while(1);
}
