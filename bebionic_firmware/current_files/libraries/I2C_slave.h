/* 
 * File:   I2C_slave.h
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 19:50
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef FOSC
#define FOSC 7370000LL
#define FCY (FOSC/2)
#endif
    
extern unsigned int value;	
extern unsigned int angle;

struct FlagType
{
	unsigned char AddrFlag:1;
	unsigned char DataFlag:1;
};
extern struct FlagType Flag;

void i2c_Init(uint8_t address);
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void);




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

