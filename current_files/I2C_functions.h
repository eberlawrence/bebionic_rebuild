/* 
 * File:   I2C_functions.h
 * Author: user
 *
 * Created on 17 de Abril de 2020, 20:31
 */

#ifndef I2C_FUNCTIONS_H
#define	I2C_FUNCTIONS_H

#define EEPROMaddr 80
#define EEPROMbaud 23

void I2CInit(void);
 
void I2CAck(void);
 
void I2CNack(void);
 
void I2CStop(void);
 
void I2CStart(void);
 
void I2CRestart(void);
 
void I2CWaitACK(void);
 
void I2CIdle(void);

void I2CWrite(unsigned char c);

void I2CRead(void);

#endif	/* I2C_FUNCTIONS_H */

