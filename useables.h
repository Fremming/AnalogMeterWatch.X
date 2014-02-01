/* 
 * File:   useables.h
 * Author: skyper
 *
 * Created on 8. januar 2014, 01:00
 */

#ifndef USEABLES_H
#define	USEABLES_H

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 16000000
#endif

#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/64000UL)))
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/64000000UL)))

#define MIN(a,b)    ( (a<b) ? (a):(b))
#define MAX(a,b)    ( (a>b) ? (a):(b))
#define ABS(x)      ( (x>0) ? (x):(-x))

#define PI          3.14159265359


/* Convert normal decimal numbers to binary coded decimal */
char decToBcd(char val) {
    return ( (val / 10 * 16) + (val%10) );
}

/* Convert binary coded decimal to normal decimal numbers */
char bdcToDec(char val) {
    return ( (val/16*10) + (val%16) );
}


#endif	/* USEABLES_H */

