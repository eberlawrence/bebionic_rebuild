/* 
 * File:   I2C_slave.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

#include <p33FJ32MC202.h>
#include "I2C_slave.h"

struct FlagType Flag;
unsigned int value = 0;	
unsigned int angle = 0;
unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device
unsigned char *RAMPtr;			//Pointer to RAM memory locations

// Init I2C communication - Slave mode
void i2c_Init(uint8_t address)
{
    _TRISB8  = 1;
    _TRISB9  = 1;
    _RB8     = 0;
    _RB9     = 0;
    
    _I2CEN   = 0; // disable I2C1
    _I2CSIDL = 0; // continue in Idle mode
    // Unimplemented bit.
    _SCLREL  = 1;
    _IPMIEN  = 0;
    _A10M    = 0; // 7 bit address mode
    _DISSLW  = 0;
    _SMEN    = 0;
    _GCEN    = 0;
    _STREN   = 1;
    _ACKDT   = 0;
    _ACKEN   = 0;
    _RCEN    = 0;
    _PEN     = 0;
    _RSEN    = 0;
    _SEN     = 0;
            
    /* clear the MI2C & SI2C Interrupts */
    _MI2C1IF = 0;                
    _SI2C1IF = 0;
    _MI2C1IE = 0;   /* enable/disable the MI2C Interrupt */
    _SI2C1IE = 1;   /* enable/disable the SI2C Interrupt */
    
    //it's a slave so don't set baud rate
    _I2CEN   = 1; // Enable I2C1 module
	I2C1ADD  = address;	// 7-bit I2C slave address must be initialised here.
    
	Flag.AddrFlag = 0;	// Initlize AddFlag
	Flag.DataFlag = 0;	// Initlize DataFlag    
}

void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void)
{
    _RB12 = 1;
    _RB12 = 0;
	unsigned char Temp;	//used for dummy read
    
	if((_R_W == 0) && (_D_A == 0))	//Address matched
		{
			Temp = I2C1RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((_R_W == 0) && (_D_A == 1))	//check for data	
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;	
				Flag.DataFlag = 1;	//next byte is data
				RAMPtr = RAMPtr + I2C1RCV;
                _SCLREL = 1;	//Release SCL1 line

			}
			else if(Flag.DataFlag)
			{
				*RAMPtr = (unsigned char)I2C1RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
				RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
				_SCLREL = 1;	//Release SCL1 line

			}
		}
	else if((_R_W == 1) && (_D_A == 0))
	{
		Temp = I2C1RCV;
		I2C1TRN = 0x10;	//Read data from RAM & send data to I2C master device
		_SCLREL = 1;	//Release SCL1 line
		while(_TBF);//Wait till all 
		RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
	}
	_SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}
