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

#define main_button _RC8
#define CHA _RB2
#define CHB _RB3
#define EA _RB6
#define EB _RB7

#define index 40
#define middle 50
#define ring 60
#define pinky 70

#include "header.h"
#include "libraries/I2C_master.h"
#include "libraries/motor_pwm.h"

int task = 0;
uint8_t addr = 10;
uint16_t timer_ms = 0;
uint16_t pulse = 0;
_Bool limit = 0;
_Bool repeated = 0;

char 


/* Motor's encoder interruption - Initializer */
void Interrupt0_Init(void)
{
    _INT2EP = 1; // negative/positive edge detect polarity              - NEGATIVE
    _INT2IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT2IP = 1; // 3-bit (0 to 7) interrupt priority config            - 001  
}

/* Movement interruption by HIGH level on channel A or B - Initializer */
void interrupt1_Init(void)
{
    _INT2R  = 17; // set the RPx as external interrupt pin               - RP17
    _INT2EP = 0;  // negative/positive edge detect polarity              - POSITIVE
    _INT2IE = 1;  // enable/disable external interrupt                   - ENABLE
    _INT2IP = 2;  // 3-bit (0 to 7) interrupt priority config            - 010
}

/* Main button interruption - Initializer */
void interrupt2_Init(void)
{
    _INT1R  = 24; // set the RPx as external interrupt pin              - RP24
    _INT1EP = 0;  // negative/positive edge detect polarity             - POSITIVE
    _INT1IE = 1;  // enable/disable external interrupt                  - ENABLE
    _INT1IP = 3;  // 3-bit (0 to 7) interrupt priority config           - 010
}

/* Timer1 interruption - Initializer */
void timer1_Init(void)
{
    PR1    = 36850; // set the period of timer1                         - 10 ms
    _TCKPS = 0;     // define prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256) - 1:1
    _T1IE  = 1;     // eneble/disable timer1 interrupt                  - ENABLE
    _TON   = 0;     // start/stop timer1                                - STOP
}

/* Do it when extern interruption 0 happens */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    if (EA){
        // forward
        limit = 0;
        pulse++;
        if (pulse == 500)
        {
            motor_pwm_config(0, "off");
            limit = 1;
        } 
    }
    else if (!EA){
        // backward
        limit = 0;
        pulse--;
        if (pulse == 0)
        {
            motor_pwm_config(0, "off");
            limit = 1;
        }
    } 
    _INT0IF = 0;
}

/* Do it when extern interruption 1 happens */
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)               
{   
    if (CHA & CHB){
        motor_pwm_config(0, "off");
    }
    else if (CHA){
        void send_command(, )
    }
    else if (CHB){
        if (repeated & limit){
            
            repeated = 0;
        }
        else{
            
            repeated = 1;
        } 
    }
    _INT2IF = 0;
}

/* Do it when extern interruption 2 happens */
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)               
{   
    _TON = 1;    
    _INT1IF = 0;
}

/* Do it when timer1 interruption happens */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    timer_ms += 10;
    
    if (main_button){
        if (timer_ms >= 6000){
            _TON = 0;
            timer_ms = 0;
        }
    }
    else {
        if (timer_ms < 800){
            _TON = 0;
            timer_ms = 0;
        }
        else if ((timer_ms >= 800) & (timer_ms < 1600)){
            _TON = 0;
            timer_ms = 0;
        }
        else if ((timer_ms >= 1600) & (timer_ms < 2400)){
            _TON = 0;
            timer_ms = 0;
        }
    }
    _T1IF = 0;
}

/*  */
void main_init(void)
{
    /* Port A I/O config */
    _TRISA4  = 0; // OUTPUT - enable/disable finger motor supplay 
    _TRISA7  = 0; // OUTPUT - enable/disable the motor driver A3906 (SLEEP flag)
    
    /* Port B I/O config */
    _TRISB2  = 1; // INPUT  - User's control signal - Channel A
    _TRISB3  = 1; // INPUT  - User's control signal - Channel B
    _TRISB5  = 1; // INPUT  - on/off flag that indicates overcurrent of the thumb motor (FL1/FL2)
    _TRISB6  = 1; // INPUT  - receive pulses from thumb motor encoder (Channel A)
    _TRISB7  = 1; // INPUT  - receive pulses from thumb motor encoder (Channel B) - Interrupt 0
    _TRISB12 = 0; // OUTPUT - enable/disable PWM1H2 to drive the thumb motor (IN1/IN3)
    _TRISB14 = 0; // OUTPUT - enable/disable PWM1H1 to drive the thumb motor (IN2/IN4)
    
    /* Port C I/O config */
    _TRISC1  = 1; // INPUT  - check if channel B or A is HIGH, if yes, call an interrupt function - Interrupt 1 
    _TRISC3  = 0; // OUTPUT - enable/disable both encoder and microcontroler supply of fingers (ring & pinky)
    _TRISC4  = 0; // OUTPUT - enable/disable both encoder and microcontroler supply of fingers (index & middle)
    _TRISC6  = 0; // OUTPUT - enable/disable PWM2H1 to drive the vibrating motor to deliver feedback to the user
    _TRISC7  = 0; // OUTPUT - enable/disable PWM2L1 to drive buzzer to deliver auditory feedback to the user
    _TRISC8  = 1; // INPUT  - set main button (on/off - change prosthesis mode - etc)
    
    timer1_Init();
    interrupt1_Init();
    interrupt2_Init();  
    i2c_Init(100000);
}
int main(void) {
    main_init();

    while(1){
        if (!CHA){
            motor_pwm_config(0, "off");
        }
        else if (!CHA & !CHB){
            motor_pwm_config(0, "off");
        }
        
    }
    return 0;
}





