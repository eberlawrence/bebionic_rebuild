/* 
 * File:   main_master.c
 * Author: Eber Lawrence
 *
 * Created on 18 de Abril de 2020, 20:00
 */

#include "header.h"
#include "libraries/I2C_master.h"

int task = 0;

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
    
    TRISBbits.TRISB5 =   1; 
    Interrupt1_Init();
    Interrupt2_Init();
    i2c_Init(100000);
    
    while(1){
        if (task == 2){
            i2c_Start();
            i2c_Write(20 << 1);
            i2c_Idle();
            i2c_Write(40);
            i2c_Idle();
            i2c_Stop();
        }       
        __delay_ms(500);      
    }
    return 0;
}

