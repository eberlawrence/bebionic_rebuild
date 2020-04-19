/*
 * File:   main.c
 * Author: Eber Lawrence
 *
 * Created on April 3, 2020, 2:57 PM
 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "header.h"
#include "libraries/I2C_slave.h"

int pulse = 0;

void PWM(unsigned int speed, char direction[10]){
    unsigned int x, y;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB14 = 0;
    PORTBbits.RB12 = 0;
    PORTBbits.RB14 = 0;
    P1TCON = 0x0002;
    P1TMR = 0;
    P1TPER = 0x7FFE; // 56.23 Hz // (range => 1 - 7FFE)
    P1DTCON1 = 0x003B;

    x = (100*speed)/50;
    y = (P1TPER / 100) * x;

    if (strcmp(direction, "forward") == 0){
        PWM1CON1 = 0x0010;
        P1DC1 = y;
        PORTBbits.RB12 = 0;
    }
    else if (strcmp(direction, "backward") == 0)
    {
        PWM1CON1 = 0x0020;
        P1DC2 = y;
        PORTBbits.RB14 = 0;
    }
    else if (strcmp(direction, "stop") == 0){
        PWM1CON1 = 0x0030;
        P1DC1 = y;
        P1DC2 = y;
    }
    else {
        PWM1CON1 = 0x0000;
    } 
    P1TCONbits.PTEN = 1;
}

void Interrupt0_Init( void )
{
    INTCON2bits.INT0EP = 0; // External interrupt edge detect polarity
    IEC0bits.INT0IE = 1; // 
    IPC0bits.INT0IP = 7; 
}

void __attribute__((interrupt, auto_psv)) _INT0Interrupt( void )               
{
    pulse++;
    if (pulse == 500){
        PORTBbits.RB2 = 1;
    }
    if (pulse == 1000){
        PORTBbits.RB3 = 1;
    }
    if (pulse == 1500)
    {
        PORTBbits.RB2 = 0;
        PORTBbits.RB3 = 0;
        pulse = 0;
    }
    IFS0bits.INT0IF = 0;
}

int main(void) {
    
    TRISBbits.TRISB2  = 0;
    TRISBbits.TRISB3  = 0;
    TRISBbits.TRISB13 = 0; 
    PORTBbits.RB13    = 1;
    
    Interrupt0_Init();
    I2C_init();
    
    while(1){
        
    }
    return 0;
}