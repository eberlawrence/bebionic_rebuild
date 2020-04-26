/* 
 * File:   I2C_master.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

/* LIBRARIES */
#include "I2C_master.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{
    _MI2C1IF = 0;		
}

/* Initialise I2C communication - Master mode */
void i2c_Init(uint32_t FSCL){   
    
    /* Config both SCL and SDA ports as INPUT */
    _TRISB8  = 1;   // SCL port                                             - INPUT
    _TRISB9  = 1;   // SDA port                                             - INPUT
    
    /* I2C1CON Register configuration - All bits '1/0' */
    _I2CEN   = 0;   // enable/disable I2C1                                  - DISABLE
 // _XXXX    = x;   // unimplemented bit. Read as '0                        - ~~
    _I2CSIDL = 0;   // discontinue/continue Idle mode                       - CONTINUE
    _SCLREL  = 0;   // release/stretch SCL clock control (Slave mode)       - ~~
    _IPMIEN  = 0;   // enable/disable IPMI support mode                     - DISABLE
    _A10M    = 0;   // 10-bit/7-bit slave address mode                      - 7-BIT
    _DISSLW  = 0;   // disable/enable slew rate control                     - ENABLE
    _SMEN    = 0;   // enable/disable SMBus I/O pin threshold               - DISABLE
    _GCEN    = 0;   // enable/disable general call address                  - DISABLE
    _STREN   = 0;   // enable/disable SCL clock stetch (Slave mode)         - ~~
    
    /* Hardware Clearable bits
    _ACKDT   = 0;   // NACK/ACK during an acknowledge   
    _ACKEN   = 0;   // enable/disable transmission of the ACKDT data bit
    _RCEN    = 0;   // enable/disable receive mode
    _PEN     = 0;   // enable/disable stop condition
    _RSEN    = 0;   // enable/disable restart condition
    _SEN     = 0;   // enable/disable start condition
    */
    
    _MI2C1IF = 0;   // enable/disable master I2C interrupt flag             - DISABLE
    _SI2C1IF = 0;   // enable/disable slave I2C interrupt flag              - DISABLE
    
    _MI2C1IE = 1;   // enable/disable master I2C interrupt event            - ENABLE
    _SI2C1IE = 0;   // enable/disable slave I2C interrupt event             - DISABLE
    
    I2C1STAT = 0x00;
    I2C1BRG  = (FOSC / FSCL) - 2; // define the SCL clock frequency (Master mode)
    _I2CEN   = 1;   // enable/disable I2C1                                  - DISABLE
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

void send_command(uint8_t addr, uint8_t data ){
    i2c_Start();
    i2c_Write(1, 0, addr);
    i2c_Idle();
    i2c_Write(0, 0, data);
    i2c_Idle();
    i2c_Stop();
}



            
 /*
    i2c_Start();
    i2c_Write(1, 0, addr);
    i2c_Idle();
    i2c_Write(0, 0, 100);
    i2c_Idle();
    i2c_Restart();
    i2c_Write(1, 1, addr);
    i2c_Idle();
    i2c_Read();
    i2c_Nack();
    i2c_Stop();*/