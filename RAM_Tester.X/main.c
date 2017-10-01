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
    TRISCbits.TRISC6 = 0;   // RC6 is the RS232 TX output
    TRISB = 0x00;           // PortB is used for output (VIC20 address bus etc)
    
    /* SETUP INTERRUPTS */
    INTCONbits.GIE = 1;     // Enable all unmased interrupts
    INTCONbits.PEIE = 1;    // Enable unmasked peripheral interrupts
    INTCONbits.T0IE = 0;    // Timer 0 interrupt overflow disabled
    INTCONbits.INTE = 0;    // External interrupt disabled
    INTCONbits.RBIE = 0;    // PORTB change interrupt disabled
    
    PIE1bits.ADIE = 0;      // ADC interrupts disabled
    PIE1bits.RCIE = 1;      // EUSART RX interrupts enabled
    PIE1bits.TXIE = 0;      // EUSART TX interrupts disabled
    PIE1bits.SSPIE = 0;     // MSSP interrupts disabled
    PIE1bits.CCP1IE = 0;    // CCP1 interrupts disabled
    PIE1bits.TMR2IE = 0;    // Timer2 to PR2 match interrupt disabled
    
    PIE2 = 0x00;            // Disable all the peripheral interrupts in PIE2
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
