/* 
 * File:   motor_pwm.h
 * Author: Eber
 *
 * Created on 20 de Abril de 2020, 03:58
 */

#ifndef MOTOR_PWM_H
#define	MOTOR_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef FOSC
#define FOSC 7370000LL
#define FCY (FOSC/2)
#endif 
    
#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC204.h>
#endif  
    
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void motor_pwm_config(unsigned int speed, char direction[10]);

void vibracall_pwm(uint8_t duty, uint32_t freq, _Bool on);

void buzzer_pwm(uint8_t duty, uint32_t freq, _Bool on);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_PWM_H */

