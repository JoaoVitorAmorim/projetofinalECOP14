#include "pic18f4520.h"
#include "config.h"
#include "atraso.h"
#include "lcd.h"
#include "adc.h"
#include "i2c.h"
#include "pwm.h"
#include "bits.h"

void itoa(unsigned int val, char* str);
void itoa1(unsigned int val1, char* str1);

void main() {

    unsigned char tmp1,tmp2;
    unsigned char temp1, temp2, mediaTemp;
    char str[6];
    char str1[6];
    char text6[9] = "   UNIFEI";
    char text7[12] = "JOAO VITOR";
    char text8[10] = "2019000724";

    ADCON1 = 0x06;
    TRISA = 0xC3;
    TRISB = 0xF0;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    lcd_init();
    adc_init();
    pwmInit();

    lcd_cmd(L_L1);
    lcd_str("UNIFEI");
    lcd_cmd(L_L2);
    lcd_str("JOAO VITOR      ");
    lcd_str("RB5 para iniciar");
    while (PORTBbits.RB5);
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Lote1 =");
    lcd_cmd(L_L2);
    lcd_str("Lote2 =");

    while (1) {
        tmp1 = (adc_amostra(0)*10) / 204;
        tmp2 = (adc_amostra(2)*10) / 204;
        lcd_cmd(L_L1 + 9);
        itoa(tmp1, str);
        itoa1(tmp2, str1);
        temp1 = str[3];
        temp2 = str1[3];
        mediaTemp = ((temp1 + temp2) / 2);

        if (mediaTemp <= 50 && mediaTemp >= 49) pwmSet1(32);
        if (mediaTemp <= 52 && mediaTemp > 50) pwmSet1(64);
        if (mediaTemp <= 53 && mediaTemp > 52) pwmSet1(92);
        if (mediaTemp == 48) pwmSet1(0);

        if (temp1 >= 50) {
            BitSet(PORTB, 1);
        }
        if (temp1 < 50) {
            BitClr(PORTB, 1);
        }

        if (temp2 >= 50) {
            BitSet(PORTB, 2);
        }
        if (temp2 < 50) {
            BitClr(PORTB, 2);
        }



        lcd_dat(temp1);
        lcd_dat(str[4]);
        lcd_dat(223);
        lcd_dat(' ');
        lcd_dat(mediaTemp);
        lcd_dat(str[4]);
        lcd_dat(223);
        lcd_cmd(L_L2 + 9);
        lcd_dat(temp2);
        lcd_dat(str[4]);
        lcd_dat(223);
        atraso_ms(10);
    }
}

void itoa(unsigned int val, char* str) {
    str[0] = (val / 10000) + 0x30;
    str[1] = ((val % 10000) / 1000) + 0x30;
    str[2] = ((val % 1000) / 100) + 0x30;
    str[3] = ((val % 100) / 10) + 0x30;
    str[4] = (val % 10) + 0x30;
    str[5] = 0;
}

void itoa1(unsigned int val1, char* str1) {
    str1[0] = (val1 / 10000) + 0x30;
    str1[1] = ((val1 % 10000) / 1000) + 0x30;
    str1[2] = ((val1 % 1000) / 100) + 0x30;
    str1[3] = ((val1 % 100) / 10) + 0x30;
    str1[4] = (val1 % 10) + 0x30;
    str1[5] = 0;
}