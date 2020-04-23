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
    
#include <p33FJ32MC202.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void motor_pwm_config(unsigned int speed, char direction[10]);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_PWM_H */

