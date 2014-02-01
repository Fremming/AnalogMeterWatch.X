#ifndef LCD_C
#define	LCD_C

#include "lcd.h"

unsigned char _cols;
unsigned char _rows;
unsigned char _backlightval = LCD_NOBACKLIGHT;

void lcd_init(unsigned char columns, unsigned char rows) {
    _cols = columns;
    _rows = rows;
}
void lcd_begin() {}
void lcd_clear() {}
void lcd_home() {}
void lcd_noDisplay() {}
void lcd_display() {}
void lcd_noBlink() {}
void lcd_blink() {}
void lcd_noCursor() {}
void lcd_cursor() {}
void lcd_scrollDisplayLeft() {}
void lcd_scrollDisplayRight() {}
void lcd_printLeft() {}
void lcd_printRight() {}
void lcd_leftToRight() {}
void lcd_rigthToLeft() {}
void lcd_shiftIncrement() {}
void lcd_shiftDecrement() {}
void lcd_noBacklight() {}
void lcd_backlight() {}
void lcd_noAutoscroll() {}
void lcd_autoscroll() {}
void lcd_createChar(unsigned char char_num, unsigned char *rows) {}
void lcd_setCursor(unsigned char x, unsigned char y) {}
void lcd_write(unsigned char _char) {}
void lcd_command(unsigned char command) {}

void lcd_print(unsigned char *text) {}

#endif	/* LCD_C */