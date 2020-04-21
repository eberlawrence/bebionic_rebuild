/*
 * File:   main_slave.c
 * Author: Eber Lawrence
 *
 * Created on April 3, 2020, 2:57 PM
 */

#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC202.h>
#endif   

#include "header.h"
#include "libraries/I2C_slave.h"
#include "libraries/pwm_generator.h"

int pulse = 0;

void Interrupt0_Init( void )
{
    _INT0EP = 0; // External interrupt edge detect polarity
    _INT0IE = 1; // 
    _INT0IP = 1; 
}

void __attribute__((interrupt, auto_psv)) _INT0Interrupt( void )               
{
    pulse++;
    if (pulse == 500){
        _RB2 = 1;
    }
    if (pulse == 1000){
        _RB3 = 1;
    }
    if (pulse == 1500)
    {
        _RB2 = 0;
        _RB3 = 0;
        pulse = 0;
    }
    _INT0IF = 0;
}

int main(void) {
    
    _TRISB2  = 0;
    _TRISB3  = 0;
    _TRISB13 = 0;
    _RB13    = 1;
    
    Interrupt0_Init();
    i2c_Init(ADDR);
    
    while(1){        

        if (value == 100){
            PWM(50, "forward");
            value = 0;
        }
    }
    return 0;
}