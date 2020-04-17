#ifndef XC_HEADER_TEMPLATE_H
#define XC_HEADER_TEMPLATE_H
 
#include <xc.h> // include processor files - each processor file is guarded.  
 
// TODO Insert appropriate #include <>
 
// TODO Insert C++ class definitions if appropriate
 
// TODO Insert declarations
 
// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
   
    <p><b>Summary:</b></p>
 
    <p><b>Description:</b></p>
 
    <p><b>Precondition:</b></p>
 
    <p><b>Parameters:</b></p>
 
    <p><b>Returns:</b></p>
 
    <p><b>Example:</b></p>
    <code>
  
    </code>
 
    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation
 
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
 
//Global Vars
#define EEPROMaddr 80
#define EEPROMbaud 23 // @FSCL = 400kHz; (FCY/FSCL - FCY/1e7) - 1
//#define EEPROMbaud 98 // @FSCL = 100kHz;  
//
extern void I2CInit(void);
extern void I2CStart(void);
extern void I2CRestart(void);
extern void I2CStop(void);
extern void I2CWaitACK(void);
extern void I2CIdle(void);
extern void I2CAck(void);
extern void I2CNack(void);
extern void I2CWrite(unsigned char c);
extern void I2CRead(void);
extern void I2CWriteReg(char addr, char byteHigh, char byteLow, char value);
extern char I2CReadReg(char addr, char byteHigh, char byteLow);
extern void I2CSequentialWriteReg(char addr, char byteHigh, char byteLow, char* value, int length);
extern void I2CSequentialReadReg(char addr, char byteHigh, char byteLow, char* buff, int length);
 
#ifdef  __cplusplus
}
#endif /* __cplusplus */
 
#endif  /* XC_HEADER_TEMPLATE_H */