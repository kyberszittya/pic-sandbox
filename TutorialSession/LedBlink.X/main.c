/*
 * File:   main.c
 * Author: keret
 *
 * Created on October 13, 2022, 12:42 AM
 */


#include "xc8_header.h"
#include <xc.h>

#define TIME_BLINK_STATE_CHANGE 2

uint8_t C = 0;



typedef enum BlinkStates {BLINK_OFF, BLINK_ON};
enum BlinkStates blink_state;

void main(void) {    
    blink_state = BLINK_OFF;
    // Timer
    TMR1 = 0;
    TMR1CS = 0;
    // Prescaler setup
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    // Timer1 enable
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IF = 0;
    PEIE = 1;
    GIE = 1;
    // Port configuration
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;
    while(1)
    {
    }    
}

void __interrupt() isr(void)
{
    if (TMR1IF)
    {
        C++;
        if (C==TIME_BLINK_STATE_CHANGE)
        {
            switch(blink_state)
            {
                case BLINK_OFF: {
                    PORTBbits.RB0 = 0;
                    blink_state = BLINK_ON;
                    break;
                }
                case BLINK_ON: {
                    PORTBbits.RB0 = 1;
                    blink_state = BLINK_OFF;
                    break;
                }
            }
            C = 0;                    
        }
        TMR1IF = 0;
    }
}