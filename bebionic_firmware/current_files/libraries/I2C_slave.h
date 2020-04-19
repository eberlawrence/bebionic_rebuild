
/* 
 * File:   main_header.h
 * Author: Eber
 *
 * Created on 18 de Abril de 2020, 19:50
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif


#define USE_I2C_Clock_Stretch	//uncomment this line if you want clock stretching featue
								//to be enabled
//Functions prototype
void I2C_init(void);
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void);

extern unsigned int value;	//RAM area which will work as EEPROM for Master I2C device
extern unsigned int angle;

struct FlagType
{
	unsigned char AddrFlag:1;
	unsigned char DataFlag:1;
};
extern struct FlagType Flag;


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

