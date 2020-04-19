#include <p33FJ32MC202.h>
#include "I2C_slave.h"

unsigned int value;	//RAM area which will work as EEPROM for Master I2C device
unsigned int angle;

struct FlagType Flag;

/*****************************************************************
		Init I2C1 Bus
*****************************************************************/
void I2C_init(void)
{
	#if !defined(USE_I2C_Clock_Stretch)
		I2C1CON = 0x8000;	//Enable I2C1 module
	#else
		I2C1CON = 0x9040;	//Enable I2C1 module, enable clock stretching
	#endif
	

	I2C1ADD = 0x50;			// 7-bit I2C slave address must be initialised here. 
	
	IFS1=0;
	Flag.AddrFlag = 0;	//Initlize AddFlag
	Flag.DataFlag = 0;	//Initlize DataFlag
	IEC1bits.SI2C1IE = 1;
}

/*
Function Name: SI2C1Interrupt
Description : This is the ISR for I2C1 Slave interrupt.
Arguments	 : None
*/
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void)
{
	unsigned char Temp;	//used for dummy read
    
	if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 0))	//Address matched
		{
			Temp = I2C1RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 1))	//check for data	
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;	
				Flag.DataFlag = 1;	//next byte is data
				#if defined(USE_I2C_Clock_Stretch)
					I2C1CONbits.SCLREL = 1;	//Release SCL1 line
				#endif
			}
			else if(Flag.DataFlag)
			{
				value = (unsigned int)I2C1RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
				#if defined(USE_I2C_Clock_Stretch)
					I2C1CONbits.SCLREL = 1;	//Release SCL1 line
				#endif
			}
		}
	else if((I2C1STATbits.R_W == 1)&&(I2C1STATbits.D_A == 0))
	{
		Temp = I2C1RCV;
		I2C1TRN = angle;	//Read data from RAM & send data to I2C master device
		I2C1CONbits.SCLREL = 1;	//Release SCL1 line
		while(I2C1STATbits.TBF);//Wait till all 
	}
	IFS1bits.SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}	