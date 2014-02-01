/* 
 * File:   serialLCD.h
 * Author: skyper
 *
 * Created on 20. januar 2014, 14:35
 */

#ifndef SERIALLCD_H
#define	SERIALLCD_H

#include "useables.h"
#include "i2c.h"

#ifndef serialLCD_ADDRESS
    #define serialLCD_ADDRESS 0x27
#endif

#define LCD_RS  0b00000001
#define LCD_EN  0b00000100
#define LCD_RW  0b00000010

void serialLCD_writeCMD(unsigned char data) {
    i2c_start();
    i2c_address(serialLCD_ADDRESS, I2C_WRITE);
    i2c_write(data | 0x08);
    i2c_stop();
}

void serialLCD_pulseEnable(unsigned char data) {
    serialLCD_writeCMD(data | LCD_EN);
    __delay_us(1);

    serialLCD_writeCMD(data & ~LCD_EN);
    __delay_us(50);
}

void serialLCD_write(unsigned char value) {
    serialLCD_writeCMD(value);
    serialLCD_pulseEnable(value);
}

void serialLCD_send(unsigned char value, unsigned char mode) {
    unsigned char highnib = value & 0xf0;
    unsigned char lownib = (value << 4) & 0xf0;
    serialLCD_write((highnib)|mode);
    serialLCD_write((lownib)|mode);
}

void serialLCD_command(unsigned char value) {
    serialLCD_send(value, 0);
}


void serialLCD_clear(void) {
    serialLCD_command(0x01);
    __delay_ms(20);
}

void serialLCD_home(void) {
    serialLCD_command(0x02);
    __delay_ms(20);
}

void serialLCD_goto(unsigned char pos) {
    serialLCD_command(0x80+pos);
    __delay_ms(20);
}

void serialLCD_writeChar(unsigned char value) {
    serialLCD_send(value,LCD_RS);
}

void serialLCD_init(void) {
    i2c_init();
    __delay_ms(50);         //power-on delay, HD44780 power-on routine itself is 10ms

    serialLCD_writeCMD(0x00);
    __delay_ms(500);        //LCD_CLK;          //stabilize RS=0 condition

    serialLCD_write(0x03 << 4);  //    lcd_write_cmd(0x20);    //function, 4-bit mode
    __delay_ms(4);
    serialLCD_write(0x03 << 4);  //    lcd_write_cmd(0x20);    //function, 4-bit mode
    __delay_ms(4);
    serialLCD_write(0x03 << 4);  //    lcd_write_cmd(0x20);    //function, 4-bit mode
    __delay_ms(1);

    serialLCD_write(0x02 << 4);  //    lcd_write_cmd(0x20);    //function, 4-bit mode

    serialLCD_command(0x20);     //    lcd_write_cmd(0x28);    //function, 4-bit x 2 lines mode

    serialLCD_command(0x08 | 0x04);//    lcd_write_cmd(0x0F);    //display on, cursor on, cursor blink on

    serialLCD_clear();

    serialLCD_command(0x06);    //    lcd_write_cmd(0x06);    //config entry mode, cursor shifts right

    serialLCD_home();
}



#endif	/* SERIALLCD_H */

