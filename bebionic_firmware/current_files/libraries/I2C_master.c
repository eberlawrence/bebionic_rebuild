/* 
 * File:   I2C_master.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

#include <p33FJ32MC202.h>
#include "I2C_master.h"

void __attribute__((interrupt, auto_psv)) _MI2C1Interrupt(void)
{
    _RB12 = 1;
    _RB12 = 0;
    _MI2C1IF = 0;		
}

// Initialise I2C communication - Master mode
void i2c_Init(uint32_t FSCL){   
    
    _TRISB8 = 1;
    _TRISB9 = 1;
    
    _I2CEN   = 0; // disable I2C1
    _I2CSIDL = 0; // continue in Idle mode
    // Unimplemented bit.
    _SCLREL  = 0; // SCL release control
    _IPMIEN  = 0;
    _A10M    = 0; // 7 bit address mode
    _DISSLW  = 0; // Slew rate control
    _SMEN    = 0;
    _GCEN    = 0;
    _STREN   = 0;
    _ACKDT   = 1;
    _ACKEN   = 0;
    _RCEN    = 0;
    _PEN     = 0;
    _RSEN    = 0;
    _SEN     = 0;

    _MI2C1IF = 0;   // Master I2C interrupt
    _SI2C1IF = 0;   // Slave I2C interrupt
    
    _MI2C1IE = 1;   // MI2C Flag
    _SI2C1IE = 0;   // SI2C Flag
    
    I2C1STAT = 0x00;
    I2C1BRG = (FOSC / FSCL) - 2; // I2C Master mode, define the SCL clock frequency
    _I2CEN = 1;  // Enable I2C
}

void i2c_Ack(void)
{
    _ACKDT = 0;      // Send ACK
    _ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(_ACKEN);
}
 
void i2c_Nack(void)
{
    _ACKDT = 1;      // Send NACK
    _ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(_ACKEN);  
}

void i2c_WaitACK(void)
{
    while(_ACKSTAT);
}

void i2c_Idle(void)
{
    while(_TRSTAT);
}

// Start I2C communication
void i2c_Start(void)
{
    _ACKDT = 0;      // Reset any ACK
    _SEN = 1;        // Start
    while(_SEN);
}

// Re-Start I2C communication
void i2c_Restart(void){
    _RSEN = 1;       // Repeated Start Condition
    while(_RSEN);
    _ACKDT = 0;      // Send ACK
    _TBF = 0;       // I2C1TRN is empty
}

// Stop I2C communication
void i2c_Stop(void)
{
    _RCEN = 0;       // receive mode not in progress
    _PEN = 1;        // Stop condition
    while(_PEN);
}

// Sends one byte of data
void i2c_Write(_Bool addr, int r_w, uint8_t data)
{
    if (addr){
        I2C1TRN = (data << 1) | r_w;
    }
    else {
        I2C1TRN = data;
    }    
    while(_TBF);
}

uint8_t i2c_Read(void)
{
    _RCEN = 1;
    __builtin_nop();
    while(!_RBF);
    return (I2C1RCV);
}
