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

// Init I2C communication - Slave mode
void i2c_Init(uint8_t address)
{
    I2C1CON = 0x8000;	// Enable I2C1 module
	I2C1ADD = address;	// 7-bit I2C slave address must be initialised here.
	Flag.AddrFlag = 0;	// Initlize AddFlag
	Flag.DataFlag = 0;	// Initlize DataFlag
	_SI2C1IE = 1; // Enable slave interruption (SI2C1)
}

void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void)
{
	unsigned char temp;	// used for dummy read
    
	if((_R_W == 0)&&(_D_A == 0))	// Address matched
		{
			temp = I2C1RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((_R_W == 0) && (_D_A == 1))	//check for data	
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;	
				Flag.DataFlag = 1;	//next byte is data
			}
			else if(Flag.DataFlag)
			{
				value = (unsigned int) I2C1RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
			}
		}
	else if((_R_W == 1) && (_D_A == 0))
	{
		temp = I2C1RCV;
		I2C1TRN = angle;	//Read data from RAM & send data to I2C master device
		while(_TBF);//Wait till all 
	}
	_SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}	