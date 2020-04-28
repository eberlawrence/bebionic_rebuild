/* 
 * File:   encoder_interrupt.h
 * Author: user
 *
 * Created on 22 de Abril de 2020, 15:54
 */

#ifndef ENCODER_INTERRUPT_H
#define	ENCODER_INTERRUPT_H

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
#include <p33FJ32MC202.h>
#endif   
    
#define CH_A     _RB2
#define CH_B     _RB3
#define ENC_A    _RB6
#define ENC_B    _RB7
    
extern uint16_t pulse;
extern _Bool sense;
extern _Bool end;
    
void Interrupt0_Init(void);

void Interrupt1_Init(void);


void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void);           

void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void);                


#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_INTERRUPT_H */

