/* 
 * File:   encoder_interrupt.c
 * Author: Eber Lawrence
 *
 * Created on 22 de Abril de 2020, 15:45
 */

#include "encoder_interrupt.h"
#include "motor_pwm.h"

uint16_t pulse = 0;
_Bool sense = 1;
_Bool end = 0;

void Interrupt0_Init(void)
{
    _INT0EP = 0; // negative/positive edge detect polarity              - POSITIVE
    _INT0IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT0IP = 1; // 3-bit (0 to 7) interrupt priority config            - 001
}

void Interrupt1_Init(void)
{
    _INT1R  = 6; // Set the RPx as external interrupt pin               - RP6
    _INT0EP = 0; // negative/positive edge detect polarity              - POSITIVE
    _INT0IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT0IP = 1; // 3-bit (0 to 7) interrupt priority config            - 001
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
    
    _INT1IF = 0;
}

