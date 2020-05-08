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

#define MAIN_BUT _RC8
#define MAG_SEN  _RB13 // MUST BE _RB1
#define CH_A     _RB10 // MUST BE _RB2
#define CH_B     _RB11 // MUST BE _RB3
#define ENC_A    _RB6
#define ENC_B    _RB7

#define VIB_CALL _RC6
#define BUZZER   _RC7

#define index_addr 10
#define middle_addr 20
#define ring_addr 30
#define pinky_addr 40

#include "header.h"
#include "libraries/I2C_master.h"
#include "libraries/motor_pwm.h"

int task = 0;
uint8_t addr = 10;
uint8_t grasp = 0;
uint16_t timer1 = 0;
uint16_t timer2 = 0;
uint16_t pulse = 0;
uint16_t feedback = 0;
_Bool limit = 0;
_Bool repeated = 0;
_Bool on = 0;
_Bool thumb_pos = 0; // the thumb could be placed in two position, i.e. opposed ('1') and non-opposed ('0') to the fingers.
_Bool stop_mov = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * FUNCTIONS
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////


void power_grasp(){
    if (CH_A) {
        send_command(index_addr, 80);
        send_command(middle_addr, 80);
        send_command(ring_addr, 80);
        send_command(pinky_addr, 80);
        motor_pwm_config(50, "forward");
    }
    else if (CH_B) {
        send_command(index_addr, 90);
        send_command(middle_addr, 90);
        send_command(ring_addr, 90);
        send_command(pinky_addr, 90);
        motor_pwm_config(50, "backward");
    }

}
void tripod_grasp(){
    
}
void finger_point_grasp(){
    
}
void key_grasp(){
    
}

void grasp_selection(){
    if (MAG_SEN){
        if (grasp == 0){
            
            power_grasp();
        }
        else {
            tripod_grasp();
        }        
    }
    else {
        if (grasp == 0){
            _RC9 = 1;
            power_grasp();
        }
        else {
            key_grasp();
        }          
    }
}

void turn_on_feedback(void){        
        VIB_CALL = 1;
        BUZZER = 1;
        __delay_ms(300);
        VIB_CALL = 0;
        BUZZER = 0;
}
void turn_off_feedback(void){        
        VIB_CALL = 1;
        __delay_ms(200);
        VIB_CALL = 0;
        __delay_ms(200);
        VIB_CALL = 1;
        __delay_ms(300);
        VIB_CALL = 0;
}
void change_grasp_block_feedback(void){        
        BUZZER = 1;
        __delay_ms(300);
        BUZZER = 0;
}
void do_something_feedback(void){        
        BUZZER = 1;
        __delay_ms(200);
        BUZZER = 0;
        __delay_ms(100);
        BUZZER = 1;
        __delay_ms(200);
        BUZZER = 0;
}
void do_anotherthing_feedback(void){        
        BUZZER = 1;
        __delay_ms(100);
        BUZZER = 0;
        __delay_ms(50);
        BUZZER = 1;
        __delay_ms(100);
        BUZZER = 0;
        __delay_ms(50);
        BUZZER = 1;
        __delay_ms(100);
        BUZZER = 0;
}


/* Motor's encoder interruption - Initializer */
void interrupt0_Init(void)
{
    _INT0EP = 1; // negative/positive edge detect polarity              - NEGATIVE
    _INT0IE = 1; // enable/disable external interrupt                   - ENABLE
    _INT0IP = 1; // 3-bit (0 to 7) interrupt priority config            - 001  
}
/* Movement interruption by HIGH level on channel A or B - Initializer */
void interrupt1_Init(void)
{
    _INT1R  = 17; // set the RPx as external interrupt pin               - RP17
    _INT1EP = 1;  // negative/positive edge detect polarity              - NEGATIVE
    _INT1IE = 1;  // enable/disable external interrupt                   - ENABLE
    _INT1IP = 1;  // 3-bit (0 to 7) interrupt priority config            - 010
}
/* Main button interruption - Initializer */
void interrupt2_Init(void)
{
    _INT2R  = 24; // set the RPx as external interrupt pin              - RP24
    _INT2EP = 1;  // negative/positive edge detect polarity             - NEGATIVE
    _INT2IE = 1;  // enable/disable external interrupt                  - ENABLE
    _INT2IP = 1;  // 3-bit (0 to 7) interrupt priority config           - 010
}
/* Timer1 interruption - Initializer */
void timer1_Init(void)
{
    PR1             = 36850; // set the period of timer1                         - 10 ms
    T1CONbits.TCKPS = 0;     // define prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256) - 1:1
    _T1IE           = 1;     // eneble/disable timer1 interrupt                  - ENABLE
    T1CONbits.TON   = 0;     // start/stop timer1                                - STOP
}

/* Do it when extern interruption 0 happens */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    if (ENC_A){
        // forward
        limit = 0;
        pulse++;
        if (pulse == 500)
        {
            motor_pwm_config(0, "off");
            limit = 1;
        } 
    }
    else if (!ENC_A){
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
    if (CH_A & CH_B){        
        motor_pwm_config(0, "off");
    }
    else if (CH_A){
        grasp_selection();
    }
    else if (CH_B){
        if (repeated & limit){
            grasp = abs(grasp - 1); // invert the grasp value
            repeated = 0;
        }
        else{
            grasp_selection();
            repeated = 1;
        } 
    }
    stop_mov = 1;
    _INT1IF = 0;
}
/* Do it when extern interruption 2 happens */
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)               
{   
    T1CONbits.TON = 1;
    _INT2IF = 0;
}
/* Do it when timer1 interruption happens */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{    
    if (!on){ // if the button is pressed and the prosthesis was off        
        on = 1; // Turn the prosthesis on
        turn_on_feedback();
        T1CONbits.TON = 0; // disable the timer  
        _RA4 = 1; // enable finger's motor supply
        _RA7 = 1; // disable SLEEP MODE MOTOR DRIVER
        _RA9 = 1; // disable POWER SAVE MODE
        _RC3 = 1; // enable finger's supply
        _RC4 = 1; // enable finger's supply
    }
        
    else if (on){ // if the button is pressed and the prosthesis was on        
        timer1 += 10;
        if (timer1 > 4000){
            on = 0; // Turn the prosthesis off
            turn_off_feedback();      
            timer1 = 0; // timer reset 
            T1CONbits.TON = 0; // disable the timer
            _RA4 = 0; // disable finger's motor supply
            _RA7 = 0; // enable SLEEP MODE MOTOR DRIVER
            _RA9 = 0; // enable POWER SAVE MODE
            _RC3 = 0; // disable finger's supply
            _RC4 = 0; // disable finger's supply
        }
    }
    
    if ((MAIN_BUT) & (timer1 != 0)) {
        
        if (timer1 <= 800){ // This will be used to change grasp block.
            // insert function or flag to change the grasp block
            change_grasp_block_feedback();        
            timer1 = 0;
            T1CONbits.TON = 0;
        }
        
        // This could be used to change configs, e.g. changing the kind of control of the prosthesis.
        else if ((timer1 > 800) & (timer1 <= 2000)){
            do_something_feedback(); 
            timer1 = 0;
            T1CONbits.TON = 0; 
        }
        else if ((timer1 > 2000) & (timer1 <= 4000)){
            do_anotherthing_feedback(); 
            timer1 = 0;
            T1CONbits.TON = 0; 
        }
    }
    _T1IF = 0;
}




/*  */
void main_init(void)
{
    _TRISC9 = 0;
    
    /* Port A I/O config */
    _TRISA4  = 0; // OUTPUT - enable/disable finger motor supplay 
    _TRISA7  = 0; // OUTPUT - enable/disable the motor driver A3906 (SLEEP flag)
    _TRISA9  = 0; // OUTPUT - enable/disable the SYNC flag that - When LOW, it reduces the power consumption (power-save mode)
    
    /* Port B I/O config */
    _TRISB13  = 1; // INPUT  - magnetic sensor - if high (Non-Opposed thumb position), if low (Opposed thumb position)           ***MUST BE _RB1***
    _TRISB10  = 1; // INPUT  - User's control signal - Channel A (* it was at I/O pin RB2, but the simulation didn't work there) ***MUST BE _RB2***
    _TRISB11  = 1; // INPUT  - User's control signal - Channel B (* it was at I/O pin RB3, but the simulation didn't work there) ***MUST BE _RB3***
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
    interrupt0_Init();
    interrupt1_Init();
    interrupt2_Init();  
    i2c_Init(100000);
}

/*  */
int main(void) {
    main_init();
    while(1){
//        if (!CH_A & !CH_B & stop_mov){
//            _RB9 = 1;
//            motor_pwm_config(0, "off");
//            _RB9 = 0;
//            stop_mov = 0;
//        }
        
    }
    return 0;
}

/* All Bebionic Grasps
 * 
 * BLOCK A - Non-Opposed
 *      Key 
 *      Finger Poit
 *      Open palm
 *      Column
 *      Mouse
 *      Relexed Hand
 * 
 * BLOCK B - Opposed
 *      Tripod
 *      Power
 *      Finger Adduction
 *      Hook
 *      Active Index
 *      Pinch
 *      Precision Closed
 *      Precision Open
 */
