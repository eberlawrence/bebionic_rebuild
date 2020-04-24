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

#include "header.h"
#include "libraries/I2C_master.h"
#include "libraries/motor_pwm.h"

int task = 0;
uint8_t addr = 10;


uint16_t timer_ms = 0;
uint16_t pulse = 0;
_Bool sense = 1;
_Bool end = 0;


void Interrupt0_Init(void)
{
    _INT2EP = 1; // negative/positive edge detect polarity              - NEGATIVE
    _INT2IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT2IP = 1; // 3-bit (0 to 7) interrupt priority config            - 001  
}

void interrupt1_Init(void)
{
    _INT1R  = 24; // set the RPx as external interrupt pin               - RP24
    _INT1EP = 0; // negative/positive edge detect polarity              - POSITIVE
    _INT1IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT1IP = 2; // 3-bit (0 to 7) interrupt priority config            - 010
}

void interrupt2_Init(void)
{
    _INT2R  = 5; // set the RPx as external interrupt pin               - RP5
    _INT2EP = 1; // negative/positive edge detect polarity              - NEGATIVE
    _INT2IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT2IP = 2; // 3-bit (0 to 7) interrupt priority config            - 010
}

void timer1_Init(void)
{
    PR1    = 36850; // set the period of timer1                         - 10 ms
    _TCKPS = 0;     // define prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256) - 1:1
    _T1IE  = 1;     // eneble/disable timer1 interrupt                  - ENABLE
    _TON   = 0;     // start/stop timer1                                - STOP
}

void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    if (sense == 1)
    {
        end = 0;
        pulse++;  
        if (pulse == 500)
        {
            motor_pwm_config(0, "off");
            sense = 0;
            end = 1;
        } 
    }
    else
    {
        end = 0;
        pulse--;
        if (pulse == 0)
        {
            motor_pwm_config(0, "off");
            sense = 1;
            end = 1;
        }
    }

        
    _INT0IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)               
{   
    _TON = 1;    
    _INT1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)               
{   
    task = 2;
    _INT2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    timer_ms += 10;
    
    if (main_button){
        if (timer_ms >= 2400){
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

void main_init(void)
{
    _TRISB3  = 0;
    _TRISB4  = 0;
    _TRISB5  = 1;
    _TRISB12 = 0;
    _TRISC8  = 1; // set main button as input
    
    timer1_Init();
    interrupt1_Init();
    interrupt2_Init();
    
    
    i2c_Init(100000);
}
int main(void) {
    main_init();

    while(1){
        
    }
    return 0;
}





/*
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
        else if (task == 2){
            i2c_Start();
            i2c_Write(1, 0, addr);
            i2c_Idle();
            i2c_Write(0, 0, 50);
            i2c_Idle();
            i2c_Restart();
            i2c_Write(1, 1, addr);
            i2c_Idle();
            i2c_Read();
            i2c_Nack();
            i2c_Stop();
            task = 0;
        }*/