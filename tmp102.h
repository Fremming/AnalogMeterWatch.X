/* 
 * File:   tmp102.h
 * Author: skyper
 *
 * Created on 16. januar 2014, 18:16
 */

#ifndef TMP102_H
#define	TMP102_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "i2c.h"

#define TMP102_ADDRESS 0x92

int tmp102_read(void) {
    char msb, lsb;
    int temp;

    i2c_start();
    i2c_address(TMP102_ADDRESS, I2C_WRITE);
    i2c_write(0x00);
    i2c_restart();
    i2c_address(TMP102_ADDRESS, I2C_READ);
    i2c_wait();
    msb = i2c_read(1);
    i2c_wait();
    lsb = i2c_read(0);
    i2c_stop();

    temp = (msb << 8) | lsb;
    temp >>= 4;

    if ( temp & (1<<1) ) {
        temp |= 0xF800;
    }

    temp /= 16;

    return (temp);
}


#ifdef	__cplusplus
}
#endif

#endif	/* TMP102_H */

