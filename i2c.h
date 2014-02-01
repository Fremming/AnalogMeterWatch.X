/* 
 * File:   i2c.h
 * Author: skyper
 *
 * Created on 4. januar 2014, 20:22
 */

#ifndef I2C_H
#define	I2C_H

#define I2C_WRITE   0
#define I2C_READ    1
    // 1k8 ohm resistors

void i2c_init(void) {
    TRISC3 = 1;
    TRISC4 = 1;

    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0x00;

    SSP1ADD = 39;

    SSP1STAT = 0b11000000;
}

void i2c_wait(void) {
    while ( ( SSP1CON2 & 0x1F ) || ( SSP1STAT & 0x04 ) );
}

void i2c_start(void) {
    i2c_wait();
    SEN1 = 1;
}

void i2c_restart(void) {
    i2c_wait();
    RSEN1 = 1;
}

void i2c_stop(void) {
    i2c_wait();
    PEN1 = 1;
}

void i2c_write(unsigned char data) {
    i2c_wait();
    SSP1BUF = data;
}

void i2c_address(unsigned char address, unsigned char mode) {
    unsigned char l_address;

    l_address = address << 1;
    l_address += mode;
    i2c_wait();
    SSP1BUF = l_address;
}

unsigned char i2c_read(unsigned char ack) {
    unsigned char i2cReadData;

    i2c_wait();
    RCEN1 = 1;
    i2c_wait();
    i2cReadData = SSP1BUF;
    i2c_wait();
    if (ack) ACKDT1 = 0;
    else ACKDT1 = 1;
    ACKEN1 = 1;

    return( i2cReadData );
}

#endif	/* I2C_H */

