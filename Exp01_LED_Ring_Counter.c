#include <REGX51.H>
void delay(void){ unsigned int i,j; for(i=0;i<200;i++) for(j=0;j<1275;j++); }
void main(void){
    unsigned char led=0x01;
    while(1){ P2=led; delay(); led=(led<<1)|(led>>7); }
}
