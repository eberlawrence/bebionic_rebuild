/*
 * File:   main.c
 * Author: user
 *
 * Created on April 3, 2020, 2:57 PM
 */

// DSPIC33FJ32MC202 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD2               // Comm Channel Select (Communicate on PGC2/EMUC2 and PGD2/EMUD2)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.





#define FOSC 7370000LL
#define FCY (FOSC/2)
#define S1 PORTBbits.RB8

#define EEPROMaddr 80
#define EEPROMbaud 23

#include <xc.h>
#include <libpic30.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int pulse = 0;
int task = 0;

void I2CInit(void)
{
    I2C1BRG = EEPROMbaud;           // @400kHz; (FCY/FSCL - FCY/1e7) - 1
    I2C1CONbits.I2CEN = 0;  // Disable I2C
    I2C1CONbits.DISSLW = 1; // Disable slew rate control
    I2C1CONbits.A10M = 0;   // 7-bit slave addr
    I2C1CONbits.SCLREL = 1; // SCL release control
    I2C1CONbits.I2CEN = 1;  // Enable I2C
    IEC1bits.MI2C1IE = 0;   // Master I2C interrupt
    IFS1bits.MI2C1IF = 0;   // MI2C Flag
}
 
void I2CAck(void)
{
    I2C1CONbits.ACKDT = 0;      // Send ACK
    I2C1CONbits.ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(I2CCONbits.ACKEN);
}
 
void I2CNack(void)
{
    I2C1CONbits.ACKDT = 1;      // Send NACK
    I2C1CONbits.ACKEN = 1;      // Initiate Acknowledge and transmit ACKDT
    while(I2CCONbits.ACKEN);  
}
 
void I2CStop(void)
{
    I2C1CONbits.RCEN = 0;       // receive mode not in progress
    I2C1CONbits.PEN = 1;        // Stop condition
    while(I2C1CONbits.PEN);
}
 
void I2CStart(void)
{
    I2C1CONbits.ACKDT = 0;      // Reset any ACK
    I2C1CONbits.SEN = 1;        // Start
    while(I2C1CONbits.SEN);
}
 
void I2CRestart(void)
{
    I2C1CONbits.RSEN = 1;       // Repeated Start Condition
    while(I2C1CONbits.RSEN);
    I2C1CONbits.ACKDT = 0;      // Send ACK
    I2C1STATbits.TBF = 0;       // I2C1TRN is empty
}
 
void I2CWaitACK(void)
{
    while(I2C1STATbits.ACKSTAT);
}
 
void I2CIdle(void)
{
    while(I2CSTATbits.TRSTAT);
}
 
void I2CWrite(unsigned char c)
{
    I2C1TRN = c;
    while(I2C1STATbits.TBF);
}
 
void I2CRead(void)
{
    I2CCONbits.RCEN = 1;
    Nop();
    while(!I2CSTATbits.RBF);
}


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


