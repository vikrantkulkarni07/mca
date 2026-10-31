#include <REGX51.H>
void delay(void){ unsigned int i,j; for(i=0;i<200;i++) for(j=0;j<1275;j++); }
void main(void){
    unsigned char count;
    while(1) for(count=0;count<=9;count++){ P2=count; delay(); }
}
