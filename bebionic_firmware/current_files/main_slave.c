/*
 * File:   main_slave.c
 * Author: Eber Lawrence
 *
 * Created on April 3, 2020, 2:57 PM
 */

#if defined(__dsPIC33FJ32MC202__)
#include <p33FJ32MC202.h>
#endif
#if defined(__dsPIC33FJ32MC204__)
#include <p33FJ32MC202.h>
#endif   

#include "header.h"
#include "libraries/I2C_slave.h"
#include "libraries/motor_pwm.h"
#include "libraries/encoder_interrupt.h"


int main(void) {
    
    _TRISB13 = 0;
    _RB13    = 1;
    
    Interrupt0_Init();
    i2c_Init(ADDR);
    
    while(1){        

        if ((value == 100) & (!end) & (sense)){
            motor_pwm_config(50, "forward");
            value = 0;
        }
        if ((value == 100) & (!end) & (!sense)){
            motor_pwm_config(50, "backward");
            value = 0;
        }
        else if (value == 50){
            motor_pwm_config(0, "off");
        }
    }
    return 0;
}