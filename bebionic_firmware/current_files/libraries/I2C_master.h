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

#define EEPROMaddr 80
#define EEPROMbaud 23

extern void I2C_init(void);
 
extern void I2CAck(void);
 
extern void I2CNack(void);
 
extern void I2CStop(void);
 
extern void I2CStart(void);
 
extern void I2CRestart(void);
 
extern void I2CWaitACK(void);
 
extern void I2CIdle(void);

extern void I2CWrite(unsigned char c);

extern void I2CRead(void);

extern void I2CWriteReg(char addr, char v);

extern char I2CReadReg(char addr, char byteHigh, char byteLow);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

