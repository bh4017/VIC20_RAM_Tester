/*
 * File:   main.c
 * Author: brian
 *
 * Created on 16 September 2017, 16:44
 */

#include <xc.h>
#include<stdio.h>
#include<stdlib.h>

/* SETUP CONFIG WORD */
// Config1
#pragma config DEBUG = 0    // ICSPCLK, ISCSPDAT Dedicated to debugger
#pragma config LVP = 0      // Low voltage programming OFF
#pragma config FCMEN = 0    // Fail-safe clock monitor OFF
#pragma config IESO = 0     // Two speed startup OFF
#pragma config BOREN = 0    // Brown-out reset disabled
#pragma config CPD = 1      // Data code protection disabled
#pragma config CP = 1       // Code protection disabled
#pragma config MCLRE = 1    // MCLR Pin is dedicated to MCLR
#pragma config PWRTE = 1    // Power-up timer disabled
#pragma config WDTE = 0     // Watchdog timer disabled
#pragma config FOSC = 4     // Internal OSC, IO on CLK IN/OUT

/* CLOCK FREQUENCY */
#define _XTAL_FREQ 8000000

void setup_hardware(void)
{
    /* SETUP CLOCK */
    OSCCONbits.IRCF = 7;    // 8Mhz internal oscillator
    OSCCONbits.SCS = 1;     // Run from internal osc
    
    /* SETUP IO */
    TRISA = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC7 = 1;   // RC7 is the RS232 RX input
    TRISB = 0x00;           // PortB is used for output (VIC20 address bus etc)
    
}

void main(void) 
{
    setup_hardware();
    PORTA = 0xff;
    
    PORTAbits.RA0 = 1;
    while(1)
    {
        PORTCbits.RC5 = 1;
        __delay_ms(500);
        PORTCbits.RC5 = 0;
        __delay_ms(500);
    }
    return;
}
