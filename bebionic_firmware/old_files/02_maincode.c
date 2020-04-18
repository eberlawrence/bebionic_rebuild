/*
 * File:   main.c
 * Author: Eber Lawrence
 *
 * Created on April 3, 2020, 2:57 PM
 */


#define S1 PORTBbits.RB8



#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "main_header.h"
#include "I2C_functions.h"


int pulse = 0;
int task = 0;




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



void __attribute__((interrupt, auto_psv)) _INT1Interrupt( void )               
{   
    task = 1;
    IFS1bits.INT1IF = 0;
}

void __attribute__((interrupt, auto_psv)) _INT2Interrupt( void )               
{   
    task = 2;
    IFS1bits.INT2IF = 0;
}



int main(void) {
    Interrupt0_Init();
    Interrupt1_Init();
    Interrupt2_Init();
    TRISBbits.TRISB2 =   0;
    TRISBbits.TRISB3 =   0;
    TRISBbits.TRISB5 =   1; 
    TRISBbits.TRISB13 =  0; 
    PORTBbits.RB13 =     1;

 
    while(1){
        if (task == 1){
            PWM(50, "forward");
            task = 0;
        }
        if (task == 2){
            PWM(50, "stop");
            task = 0;
        }
        
    }
    return 0;
}


