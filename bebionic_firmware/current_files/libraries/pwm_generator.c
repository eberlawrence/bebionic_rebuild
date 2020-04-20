
#include "pwm_generator.h"

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
