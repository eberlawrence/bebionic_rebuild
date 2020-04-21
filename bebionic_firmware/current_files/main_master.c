/* 
 * File:   main_master.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC204.h>
#endif   

#include "header.h"
#include "libraries/I2C_master.h"

int task = 0;
uint8_t addr = 10;

void Interrupt1_Init( void )
{
    RPINR0bits.INT1R = 5; // Define the pin number, according to RPx
    INTCON2bits.INT1EP = 0; // External interrupt edge detect polarity
    IEC1bits.INT1IE = 1; // 
    IPC5bits.INT1IP = 1; 
}

void Interrupt2_Init( void )
{
    RPINR1bits.INT2R = 5; // Define the pin number, according to RPx
    INTCON2bits.INT2EP = 1; // External interrupt edge detect polarity
    IEC1bits.INT2IE = 1; // 
    IPC7bits.INT2IP = 1; 
}

void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt( void )               
{   
    task = 1;
    IFS1bits.INT1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt( void )               
{   
    task = 2;
    IFS1bits.INT2IF = 0;
}

int main(void) {
    _TRISB4  = 0;
    _TRISB5  = 1;
    _TRISB12 = 0;
    
    Interrupt1_Init();
    Interrupt2_Init();
    i2c_Init(100000);

    while(1){
        if (task == 1){
            i2c_Start();
            i2c_Write(1, 0, addr);
            i2c_Idle();
            i2c_Write(0, 0, 100);
            i2c_Idle();
            i2c_Restart();
            i2c_Write(1, 1, addr);
            i2c_Idle();
            i2c_Read();
            i2c_Nack();
            i2c_Stop();
            
            task = 0;
        } 
    }
    return 0;
}

