/* 
 * File:   I2C_master.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

#include <p33FJ32MC202.h>
#include "I2C_master.h"

// Initialise I2C communication - Master mode
void i2c_Init(uint32_t FSCL){   
    I2C1BRG = (FOSC / FSCL) - 2; // I2C Master mode, define the SCL clock frequency
    _I2CEN = 0;  // Disable I2C
    _DISSLW = 1; // Disable slew rate control
    _A10M = 0;   // 7-bit slave addr
    _SCLREL = 1; // SCL release control
    _I2CEN = 1;  // Enable I2C
    _MI2C1IE = 0;   // Master I2C interrupt
    _MI2C1IF = 0;   // MI2C Flag
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
void i2c_Write(uint8_t data)
{
    I2C1TRN = data;
    while(_TBF);
}
