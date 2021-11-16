#include <xc.h>
#include "timer.h"
#include "IO.h"
#include "PWM.h"
#include "robot.h"
#include "adc.h"
#include "main.h"

long timestamp;

//Initialisation d?un timer 32 bits //////////////////////////////////

void InitTimer23(void) {
    T3CONbits.TON = 0; // Stop any 16-bit Timer3 operation
    T2CONbits.TON = 0; // Stop any 16/32-bit Timer3 operation
    T2CONbits.T32 = 1; // Enable 32-bit Timer mode
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TCKPS = 0b01; // Select 1:1 Prescaler
    PR3 = 0x004C; // Load 32-bit period value (msw)
    PR2 = 0x4B40; // Load 32-bit period value (lsw)
    IPC2bits.T3IP = 0x01; // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer3 interrupt
    T2CONbits.TON = 1; // Start 32-bit Timer
    /* Example code for Timer3 ISR */
}

unsigned char toggle = 0;
// Interruption du timer 32 b i t s sur 2?3

/*void __attribute__((interrupt, no_auto_psv))_T3Interrupt(void) {
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    LED_ORANGE = !LED_ORANGE;
    if (toggle == 0) {
        PWMSetSpeed(20, MOTEUR_DROIT);
        PWMSetSpeed(20, MOTEUR_GAUCHE);
        toggle = 1;
    } else {
        PWMSetSpeed(-20, MOTEUR_DROIT);
        PWMSetSpeed(-20, MOTEUR_GAUCHE);
        toggle = 0;
    }
}
 * */
void __attribute__((interrupt, no_auto_psv))_T3Interrupt(void) {
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    //LED_ORANGE = !LED_ORANGE;
//    if (toggle == 0) {
//        PWMSetSpeedConsigne(20, MOTEUR_DROIT);
//        PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
//        toggle = 1;
//    } else {
//        PWMSetSpeedConsigne(-20, MOTEUR_DROIT);
//        PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
//        toggle = 0;
//    }
}
//Initialisation d?un timer 16 bits ////////////////////////////////////////////////////////

void InitTimer1(void) {
    //Timer1 pour horodater les mesures (1ms)
    T1CONbits.TON = 0; // Disable Timer
    SetFreqTimer1 (250);
    //T1CONbits.TCKPS = 0b11; //Prescaler
    //11 = 1:256 prescale value
    //10 = 1:64 prescale value
    //01 = 1:8 prescale value
    //00 = 1:1 prescale value
    T1CONbits.TCS = 0; //clock source = internal clock
    //PR1 = 40000000/256/(50*5); // 0x1388;

    IFS0bits.T1IF = 0; // Clear Timer Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer interrupt
    T1CONbits.TON = 1; // Enable Timer
}

//Interruption du timer 1

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    // Rezset du flag
    IFS0bits.T1IF = 0;
    
    // Verification
    //LED_BLEUE = !LED_BLEUE;
    
    // Conversion ADC
    ADC1StartConversionSequence();
    
    // Commande moteurs
    PWMUpdateSpeed();
}

void SetFreqTimer1 ( float freq )
{
T1CONbits.TCKPS = 0b00; //00 = 1:1 pre s c a l e r value
if(FCY / freq > 65535)
{
T1CONbits.TCKPS = 0b01; //01 = 1:8 p r e s c a l e r value
if(FCY / freq / 8 > 65535)
{
T1CONbits.TCKPS = 0b10; //10 = 1:64 p r e s c a l e r value
if(FCY / freq / 64 > 65535)
{
T1CONbits.TCKPS = 0b11; //11 = 1:256 p r e s c a l e r value
PR1 = ( int )(FCY / freq / 256);
}
else
PR1 = ( int )(FCY / freq / 64);
}
else
PR1 = ( int )(FCY / freq / 8 ) ;
}
else
PR1 = ( int )(FCY / freq ) ;
}
 /////////////////////////   T4   ////////////////////////////////////
void InitTimer4(void) {
    //Timer1 pour horodater les mesures (1ms)
    T4CONbits.TON = 0; // Disable Timer
    SetFreqTimer4 (1000);
    T4CONbits.TCS = 0; //clock source = internal clock

    IFS1bits.T4IF = 0; // Clear Timer Interrupt Flag
    IEC1bits.T4IE = 1; // Enable Timer interrupt
    T4CONbits.TON = 1; // Enable Timer
}
void SetFreqTimer4 ( float freq )
{
T4CONbits.TCKPS = 0b00; //00 = 1:1 pre s c a l e r value
if(FCY / freq > 65535)
{
T4CONbits.TCKPS = 0b01; //01 = 1:8 p r e s c a l e r value
if(FCY / freq / 8 > 65535)
{
T4CONbits.TCKPS = 0b10; //10 = 1:64 p r e s c a l e r value
if(FCY / freq / 64 > 65535)
{
T4CONbits.TCKPS = 0b11; //11 = 1:256 p r e s c a l e r value
PR1 = ( int )(FCY / freq / 256);
}
else
PR1 = ( int )(FCY / freq / 64);
}
else
PR1 = ( int )(FCY / freq / 8 ) ;
}
else
PR1 = ( int )(FCY / freq ) ;
}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void) {
    // Rezset du flag
    IFS1bits.T4IF = 0;
    // incrementation
    timestamp++;
     // machine d'etat
    OperatingSystemLoop();
    // Verification
    //LED_BLEUE = !LED_BLEUE;

}