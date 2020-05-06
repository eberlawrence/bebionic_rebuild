/* 
 * File:   I2C_slave.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

/* LIBRARIES */
#include "I2C_slave.h"

/* VARIABLES */

uint8_t value = 0;	
unsigned int angle = 0;

/* FUNCTIONS */

/* Initialise I2C communication - Slave mode */
void i2c_Init(uint8_t addr){   
    
    /* Config both SCL and SDA ports as INPUT */
    _TRISB8  = 1;    // SCL port                                             - INPUT
    _TRISB9  = 1;    // SDA port                                             - INPUT
    
    /* I2C1CON Register configuration - All bits '1/0' */
    _I2CEN   = 0;    // enable/disable I2C1                                  - DISABLE
 // _XXXX    = x;    // unimplemented bit. Read as '0                        - ~~
    _I2CSIDL = 0;    // discontinue/continue Idle mode                       - CONTINUE
    _SCLREL  = 1;    // release/stretch SCL clock control (Slave mode)       - ~~
    _IPMIEN  = 0;    // enable/disable IPMI support mode                     - DISABLE
    _A10M    = 0;    // 10-bit/7-bit slave address mode                      - 7-BIT
    _DISSLW  = 0;    // disable/enable slew rate control                     - ENABLE
    _SMEN    = 0;    // enable/disable SMBus I/O pin threshold               - DISABLE
    _GCEN    = 0;    // enable/disable general call address                  - DISABLE
    _STREN   = 1;    // enable/disable SCL clock stetch (Slave mode)         - ~~
    
    /* Hardware Clearable bits
    _ACKDT   = 0;    // NACK/ACK during an acknowledge   
    _ACKEN   = 0;    // enable/disable transmission of the ACKDT data bit
    _RCEN    = 0;    // enable/disable receive mode
    _PEN     = 0;    // enable/disable stop condition
    _RSEN    = 0;    // enable/disable restart condition
    _SEN     = 0;    // enable/disable start condition
    */
    
    _MI2C1IF = 0;    // enable/disable master I2C interrupt flag             - DISABLE
    _SI2C1IF = 0;    // enable/disable slave I2C interrupt flag              - DISABLE
    
    _MI2C1IE = 0;    // enable/disable master I2C interrupt event            - ENABLE
    _SI2C1IE = 1;    // enable/disable slave I2C interrupt event             - DISABLE
    
    _MI2C1IP = 0;    // 3-bit (0 to 7) master I2C interrupt priority config  - 000
    _SI2C1IP = 1;    // 3-bit (0 to 7) slave I2C interrupt priority config   - 010
    
    I2C1STAT = 0x00; // I2C status register 
    
    /* it's a slave so don't set baud rate */
    I2C1ADD  = addr; // 7-bit I2C slave address (Slave mode)
    _I2CEN   = 1;    // enable/disable I2C1                                  - DISABLE
}

void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void)
{
	uint8_t aux_addr;	//used for dummy read
    
	if((_R_W == 0) && (_D_A == 0))	//Address matched
		{
			aux_addr = I2C1RCV;		//dummy read
		}
	else if((_R_W == 0) && (_D_A == 1))	//check for data	
		{
            value = (uint8_t) I2C1RCV;// store data into RAM                
            //_SCLREL = 1;	//Release SCL1 line
		}
	else if((_R_W == 1) && (_D_A == 0))
	{
		aux_addr = I2C1RCV;
		I2C1TRN = ADDR;	//Read data from RAM & send data to I2C master device
		_SCLREL = 1;	//Release SCL1 line
		while(_TBF);//Wait till all 
	}
	_SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}
