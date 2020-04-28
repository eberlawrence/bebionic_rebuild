/* 
 * File:   motor_pwm.c
 * Author: Eber
 *
 * Created on 20 de Abril de 2020, 03:58
 */

#include "motor_pwm.h"

void motor_pwm_config(unsigned int speed, char direction[10]){
    unsigned int x, y;
    _TRISB12 = 0;
    _TRISB14 = 0;
    _RB12 = 0;
    _RB14 = 0;
    P1TCON = 0x0002;
    P1TMR = 0;
    P1TPER = 0x7FFE; // 56.23 Hz // (range => 1 - 7FFE)
    P1DTCON1 = 0x003B;

    x = (100*speed)/50;
    y = (P1TPER / 100) * x;

    if (strcmp(direction, "off") == 0){
        PWM1CON1 = 0x0000;
        _RB12 = 0;
        _RB14 = 0;
    }
    else if (strcmp(direction, "forward") == 0){
        PWM1CON1 = 0x0010;
        P1DC1 = y;
        _RB12 = 0;
    }
    else if (strcmp(direction, "backward") == 0)
    {
        PWM1CON1 = 0x0020;
        P1DC2 = y;
        _RB14 = 0;
    }
    else if (strcmp(direction, "break") == 0){
        PWM1CON1 = 0x0030;
        P1DC1 = y;
        P1DC2 = y;
    }
    else {
        PWM1CON1 = 0x0000;
    } 
    _PTEN = 1;
}


#if defined(__dsPIC33FJ32MC204__)

void vibracall_pwm(uint8_t duty, uint32_t freq, _Bool on){
    unsigned int x, y;
    _TRISC6 = 0;
    _RC6 = 0;
    P2TCON = 0x0002;
    P2TMR = 0;
    P2TPER = (FOSC / (4 * freq)) - 1; 
    P2DTCON1 = 0x003B;
    
    x = (100 * duty) / 50;
    y = (P2TPER / 100) * x;
    
    if (on){
        PWM2CON1 = 0x0010;
        P2DC1 = y;
    }
    else {
        PWM1CON1 = 0x0000;
        _RC6 = 0;
    }
    P2TCONbits.PTEN = 1;
}

void buzzer_pwm(uint8_t duty, uint32_t freq, _Bool on){
    unsigned int x, y;
    _TRISC7 = 0;
    _RC7 = 0;
    P2TCON = 0x0002;
    P2TMR = 0;
    P2TPER = (FOSC / (4 * freq)) - 1; 
    P2DTCON1 = 0x003B;
    
    x = (100 * duty) / 50;
    y = (P2TPER / 100) * x;
    
    if (on){
        PWM2CON1 = 0x0001;
        P2DC1 = y;
    }
    else {
        PWM2CON1 = 0x0000;
        _RC7 = 0;
    }
    P2TCONbits.PTEN = 1;
}

#endif