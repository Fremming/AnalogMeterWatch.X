/*
 * File:   main.c
 * Author: skyper
 *
 * Created on 3. januar 2014, 15:13
 */


/*

 * @todo:
 * -Test i2c
 * -Button inputs (Interrupts?) x 2 (Time up and Time down)
 * -UART
 *
 */

#include <pic18.h>
#include <htc.h>
#include "useables.h"
#include "i2c.h"
#include "DS1307.h"
#include "lcd.h"

/* Configuration */
#pragma config IESO=OFF, FOSC=INTIO67/*ECHPIO6*/, PRICLKEN=ON, FCMEN=OFF, PLLCFG=OFF, BOREN=SBORDIS,\
               BORV=190, PWRTEN=OFF, WDTPS=32768, WDTEN=OFF, P2BMX=PORTB5, CCP2MX=PORTC1,\
               PBADEN=OFF, CCP3MX=PORTB5, MCLRE=EXTMCLR, HFOFST=OFF, T3CMX=PORTC0, DEBUG=OFF,\
               STVREN=OFF, XINST=OFF, LVP=OFF, CP0=OFF, CP1=OFF, CPD=OFF, CPB=OFF, WRT0=OFF,\
               WRT1=OFF, WRTB=OFF, WRTC=OFF, WRTD=OFF, EBTR0=OFF, EBTR1=OFF, EBTRB=OFF

/* Definitions */
#define LED_TEST LATBbits.LATB0     //Pin 21

void interrupt ISR(void);
void setup_pwm(void);
void write_rtc(unsigned char address, unsigned char command);
unsigned char read_rtc(unsigned char pos);

int main(void) {
    OSCCON = 0b01111010;
    CCP4MD = 1;

    TRISB = 0x00;
    PORTB = 0x00;

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ADON = 0;

    setup_pwm();
    CCPR1L = 128; // 20 = 1, 38 = 2, 57 = 3, 85 = 4, 128 = 5
    CCPR2L = 20; // 20 = 1, 38 = 2, 57 = 3, 85 = 4, 128 = 5

    lcd_init(16, 2);

    lcd_write('J');
    lcd_write('o');
    lcd_write('h');
    lcd_write('n');


    char test = 0;

    for(;;) {
        LED_TEST = 1;
        __delay_ms(500);
        if (test == 127) test = 0;
        test++;
        CCPR1L = test;
        LED_TEST = 0;
        __delay_ms(500);
    }
    return 0;
}

void setup_pwm(void) {
    TRISC1 = 0;
    TRISC2 = 0;
    PORTC = 0;
    
    PR2 = 0b01111110;
    T2CON = 0b00000101;
    CCP1CON = 0b00111100;
    CCP2CON = 0b00111100;
}


void interrupt ISR (void) {

}

