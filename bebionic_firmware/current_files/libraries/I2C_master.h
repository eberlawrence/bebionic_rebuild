/* 
 * File:   I2C_master.h
 * Author: Eber
 *
 * Created on 18 de Abril de 2020, 22:36
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

/* DEFINITIONS */
#define delay 0.00000012 // Used to set the clock frequency (According to specifications = 120 ns)

#ifndef FOSC
#define FOSC 7370000LL
#define FCY (FOSC/2)
#endif

/* LIBRARIES */
#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC204.h>
#endif   
    
/* FUNCTIONS */    
void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void);

void i2c_Init(uint32_t FSCL);
void i2c_Ack(void); 
void i2c_Nack(void);
void i2c_WaitACK(void);
void i2c_Idle(void);
void i2c_Start(void);
void i2c_Restart(void);
void i2c_Stop(void);
void i2c_Write(_Bool addr, int r_w, uint8_t data);
uint8_t i2c_Read(void);
void send_command(uint8_t addr, uint8_t data );

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

