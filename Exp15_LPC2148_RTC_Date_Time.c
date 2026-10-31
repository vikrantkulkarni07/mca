/*
 * LPC2148 RTC with UART0 output. Based on the manual's RTC + UART approach.
 * Assumes PCLK=15 MHz and 32.768 kHz RTC crystal; add Keil startup file.
 */
#include <LPC214x.h>
#include <stdio.h>
void delay(unsigned int t){ volatile unsigned int i,j; for(i=0;i<t;i++) for(j=0;j<2400;j++); }
void UART0_Init(void){
    PINSEL0|=0x00000005; U0LCR=0x83; U0DLM=0; U0DLL=97; U0FDR=0x10; U0LCR=0x03;
}
void UART0_TxChar(char c){ while(!(U0LSR&0x20)); U0THR=c; }
void UART0_TxString(char *s){ while(*s) UART0_TxChar(*s++); }
void RTC_Init(void){
    CCR=0x00; ILR=0x03; CIIR=0x00; AMR=0xFF; CCR=0x11;
}
void RTC_SetTime(void){
    SEC=0; MIN=30; HOUR=10;
    DOM=31; MONTH=10; YEAR=2026; DOW=6; DOY=304;
}
int main(void){
    char buffer[60];
    UART0_Init(); RTC_Init(); RTC_SetTime();
    while(1){
        sprintf(buffer,"Time: %02d:%02d:%02d\r\n",HOUR,MIN,SEC); UART0_TxString(buffer);
        sprintf(buffer,"Date: %02d/%02d/%04d\r\n\r\n",DOM,MONTH,YEAR); UART0_TxString(buffer);
        delay(500);
    }
}
