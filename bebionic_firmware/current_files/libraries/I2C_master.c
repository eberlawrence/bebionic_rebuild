
#include <p33FJ32MC202.h>
#include "I2C_master.h"

void I2C_init(void)
{   
    I2C1BRG = EEPROMbaud;   // @400kHz; (FCY/FSCL - FCY/1e7) - 1
    I2C1CON = 0x8000;
    IEC1bits.MI2C1IE = 1;   // Master I2C interrupt
}

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{    
    IFS1bits.MI2C1IF = 0;   // MI2C Flag
}

void I2CAck(void)
{
    I2C1CONbits.ACKDT = 0;      // Send ACK
    I2C1CONbits.ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(I2CCONbits.ACKEN);
}
 
void I2CNack(void)
{
    I2C1CONbits.ACKDT = 1;      // Send NACK
    I2C1CONbits.ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(I2CCONbits.ACKEN);  
}
 
void I2CStop(void)
{
    I2C1CONbits.RCEN = 0;       // receive mode not in progress
    I2C1CONbits.PEN = 1;        // Stop condition
    while(I2C1CONbits.PEN);
}
 
void I2CStart(void)
{
    I2C1CONbits.ACKDT = 0;      // Reset any ACK
    I2C1CONbits.SEN = 1;        // Start
    while(I2C1CONbits.SEN);
}
 
void I2CRestart(void)
{
    I2C1CONbits.RSEN = 1;       // Repeated Start Condition
    while(I2C1CONbits.RSEN);
    I2C1CONbits.ACKDT = 0;      // Send ACK
    I2C1STATbits.TBF = 0;       // I2C1TRN is empty
}
 
void I2CWaitACK(void)
{
    while(I2C1STATbits.ACKSTAT);
}
 
void I2CIdle(void)
{
    while(I2CSTATbits.TRSTAT);
}
 
void I2CWrite(unsigned char c)
{
    I2C1TRN = c;
    while(I2C1STATbits.TBF);
}
 
void I2CRead(void)
{
    I2CCONbits.RCEN = 1;
    //Nop();
    while(!I2CSTATbits.RBF);
}

void I2CWriteReg(char addr, char v)
{
    // Start Condition
    I2CStart();
    // EEPROM Addr
    I2CWrite((addr<<1)&0xFE);
    I2CIdle();
    // Value
    I2CWrite(v);
    I2CIdle();
    // Stop
    I2CStop();
}
 
 
char I2CReadReg(char addr, char byteHigh, char byteLow)
{
    char temp;
    // Start Condition
    I2CStart();
    // EEPROM Addr
    I2CWrite((addr<<1)&0xFE);
    I2CIdle();
    // Addr High Byte
    I2CWrite(byteHigh);
    I2CIdle();
    // Addr Low Byte
    I2CWrite(byteLow);
    I2CIdle();
    // Restart
    I2CRestart();
    I2CWrite((addr<<1)|0x01);
    I2CIdle();  
    I2CRead();
    I2CNack();
    I2CStop();
    temp = I2C1RCV;
    return temp;
}

