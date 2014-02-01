/* 
 * File:   DS1307.h
 * Author: skyper
 *
 * Created on 8. januar 2014, 00:52
 */

#ifndef DS1307_H
#define	DS1307_H

#include "i2c.h"
#include "useables.h"

#ifndef DS1307_ADDRESS
    #define DS1307_ADDRESS 0x68//  0b1101000 DS1307 7bit address 0x68 0x01101000
#endif

void setDateDS1307() {};
void getDateDS1307() {};


unsigned char read_rtc(unsigned char pos) {
    unsigned char read_byte;

    i2c_start();
    i2c_address(DS1307_ADDRESS, I2C_WRITE);
    i2c_write(pos);
    i2c_restart();
    i2c_address(DS1307_ADDRESS, I2C_READ);
    read_byte = i2c_read(0);
    i2c_stop();
    return read_byte;

}

void write_rtc(unsigned char address, unsigned char command) {
    i2c_start();
    i2c_address(DS1307_ADDRESS, I2C_WRITE);
    i2c_write(address);
    i2c_write(command);
    i2c_stop();
}

#endif	/* DS1307_H */

