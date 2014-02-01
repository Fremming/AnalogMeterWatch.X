/* 
 * File:   lcd.h
 * Author: skyper
 *
 * Created on 24. januar 2014, 23:15
 */

#ifndef LCD_H
#define	LCD_H

#include "useables.h"
#include "i2c.h"

#ifndef LCD_ADDRESS
    #define LCD_ADDRESS 0x27
#endif

#define LCD_RS  0b00000001          // Register select bit
#define LCD_EN  0b00000100          // Enable bit
#define LCD_RW  0b00000010          // Read/Write bit

// Commands
#define LCD_CLEARDISPLAY    0x01    // 0b00000001
#define LCD_RETURNHOME      0x02    // 0b00000010
#define LCD_ENTRYMODESET    0x04    // 0b00000100
#define LCD_DISPLAYCONTROL  0x08    // 0b00001000
#define LCD_CURSORSHIFT     0x10    // 0b00010000
#define LCD_FUNCTIONSET     0x20    // 0b00100000
#define LCD_SETCGRAMADDR    0x40    // 0b01000000
#define LCD_SETDDRAMADDR    0x80    // 0b10000000

// flags for display entry mode
#define LCD_ENTRYRIGHT      0x00
#define LCD_ENTRYLEFT       0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON       0x04
#define LCD_DISPLAYOFF      0x00
#define LCD_CURSORON        0x02
#define LCD_CURSOROFF       0x00
#define LCD_BLINKON         0x01
#define LCD_BLINKOFF        0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE     0x08
#define LCD_CURSORMOVE      0x00
#define LCD_MOVERIGHT       0x04
#define LCD_MOVELEFT        0x00

// flags for function set
#define LCD_8BITMODE        0x10
#define LCD_4BITMODE        0x00
#define LCD_2LINE           0x08
#define LCD_1LINE           0x00
#define LCD_5x10DOTS        0x04
#define LCD_5x8DOTS         0x00

// flags for backlight control
#define LCD_BACKLIGHT       0x08
#define LCD_NOBACKLIGHT     0x00

unsigned char _cols;
unsigned char _rows;
unsigned char _backlightval = LCD_NOBACKLIGHT;
unsigned char _displayFunction;
unsigned char _displayControl;
unsigned char _displayMode;
unsigned char _numlines;

void lcd_eWrite(unsigned char data) {
    i2c_start();
    i2c_address(LCD_ADDRESS, I2C_WRITE);
    i2c_write(data | _backlightval);
    i2c_stop();
}

void lcd_pulse(unsigned char data) {
    lcd_eWrite(data | LCD_EN);
    __delay_us(1);
    lcd_eWrite(data & ~LCD_EN);
    __delay_us(1);
}

void lcd_write4bits(unsigned char value) {
    lcd_eWrite(value);
    lcd_pulse(value);
}

void lcd_send(unsigned char value, unsigned char mode) {
    unsigned char msb = value & 0xF0;
    unsigned char lsb = (value << 4) & 0xF0;
    lcd_write4bits(msb|mode);
    lcd_write4bits(lsb|mode);
}


// Functions
void lcd_write(unsigned char _char) {
    lcd_send(_char, LCD_RS);
}

void lcd_command(unsigned char command) {
    lcd_send(command, 0);
}

void lcd_clear(void) {
    lcd_command(LCD_CLEARDISPLAY);
    __delay_ms(20);
}

void lcd_home(void) {
    lcd_command(LCD_RETURNHOME);
    __delay_ms(20);
}

void lcd_setCursor(unsigned char column, unsigned char row) {
    char row_offsets[] = {0x00, 0x40, 0x14, 0x54 };
    if ( row > _numlines) {
        row = _numlines-1;
    }
    lcd_command(LCD_SETDDRAMADDR | (column + row_offsets[row]));
}

void lcd_noDisplay(void) {
    _displayControl &= ~LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl);
}

void lcd_display(void) {
    _displayControl |= LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl);
}

void lcd_noCursor(void) {
    _displayControl &= ~LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl );
}

void lcd_cursor(void) {
    _displayControl |= LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl );
}

void lcd_noBlink(void) {
    _displayControl &= ~LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl );
}

void lcd_blink(void) {
    _displayControl |= LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | _displayControl );
}

void lcd_scrollDisplayLeft(void) {
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scrollDisplayRight(void) {
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcd_leftToRight(void) {
    _displayMode |= LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | _displayMode);
}

void lcd_rigthToLeft(void) {
    _displayMode &= ~LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | _displayMode);
}

void lcd_noAutoscroll(void) {
    _displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | _displayMode);
}

void lcd_autoscroll(void) {
    _displayMode |= LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | _displayMode);
}

void lcd_createChar(unsigned char location, unsigned char charmap[]) {
    location &= 0x7;
    lcd_command(LCD_SETCGRAMADDR | (location << 3));
    for (char i=0; i<8; i++) {
        lcd_write(charmap[i]);
    }
}

void lcd_noBacklight(void) {
    _backlightval = LCD_NOBACKLIGHT;
    lcd_eWrite(0);
}

void lcd_backlight(void) {
    _backlightval = LCD_BACKLIGHT;
    lcd_eWrite(0);
}


void lcd_print(unsigned char *text) {
    char byteVal;
    // For each character
    lcd_write(byteVal);
}

void lcd_begin(unsigned char cols, unsigned char lines/*, unsigned char dotsize*/) {
    if (lines > 1) _displayFunction |= LCD_2LINE;
    _numlines = lines;

    /*
     if ((dotsize != 0) && (lines == 1)) _displayFunction |= LCD_5x10DOTS;
     */

    __delay_ms(50);         //power-on delay, HD44780 power-on routine itself is 10ms

    lcd_eWrite(_backlightval);
    __delay_ms(500);


    /* Try to start in 4 bit mode */
    lcd_write4bits(0x03 << 4);
    __delay_ms(4);
    lcd_write4bits(0x03 << 4);
    __delay_ms(4);
    lcd_write4bits(0x03 << 4);
    __delay_ms(1);
    lcd_write4bits(0x02 << 4);
    /* End of rutine */


    lcd_command(LCD_FUNCTIONSET | _displayFunction);
    
    _displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_display();

    lcd_clear();

    _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    lcd_command(LCD_ENTRYMODESET | _displayMode);

    lcd_home();
}

void lcd_init(unsigned char columns, unsigned char rows) {
    _cols = columns;
    _rows = rows;

    i2c_init();

    _displayFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    lcd_begin(_cols, _rows);
}


#endif	/* LCD_H */

