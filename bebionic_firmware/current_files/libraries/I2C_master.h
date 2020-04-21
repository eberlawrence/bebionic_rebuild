/* 
 * File:   I2C_master.h
 * Author: Eber
 *
 * Created on 18 de Abril de 2020, 22:36
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif
      
#ifndef FOSC
#define FOSC 7370000LL
#define FCY (FOSC/2)
#endif

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void);

void i2c_Init(uint32_t FSCL);
void i2c_Ack(void); 
void i2c_Nack(void);
void i2c_WaitACK(void);
void i2c_Idle(void);
void i2c_Start(void);
void i2c_Restart(void);
void i2c_Stop(void);
void i2c_Write(_Bool addr, int r_w, uint8_t data);
uint8_t i2c_Read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

