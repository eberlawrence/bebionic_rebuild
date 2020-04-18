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

extern void I2CInit(void);
 
extern void I2CAck(void);
 
extern void I2CNack(void);
 
extern void I2CStop(void);
 
extern void I2CStart(void);
 
extern void I2CRestart(void);
 
extern void I2CWaitACK(void);
 
extern void I2CIdle(void);

extern void I2CWrite(unsigned char c);

extern void I2CRead(void);

extern void I2CWriteReg(char addr, char byteHigh, char byteLow, char value);

extern char I2CReadReg(char addr, char byteHigh, char byteLow);

extern void I2CSequentialWriteReg(char addr, char byteHigh, char byteLow, char* value, int length);

extern void I2CSequentialReadReg(char addr, char byteHigh, char byteLow, char* buff, int length);

#endif	/* I2C_FUNCTIONS_H */

