/* 
 * File:   I2C_slave.h
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 19:50
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef FOSC
#define FOSC 7370000LL
#define FCY (FOSC/2)
#endif
    
#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC202.h>
#endif   
    

#define ADDR 10
    
extern uint8_t value;	

extern unsigned int angle;


void i2c_Init(uint8_t addr);

void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

