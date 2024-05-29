/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: pwm.c
 * Created on: 13 Feb 2024
 * Date Last Updated: 13/02/2024
 * Update Description:
 *    Defined setRGBDutyCycle function.
 * Author: Finlay Harris
 **************************************************************************/

#include "pwm.h"

/**************************************************************************
 * Global Variables:
 *    blueDutyCycle - Stores the current duty cycle value for the blue LED.
 *    greenDutyCycle - Stores the current duty cycle value for the green LED.
 * These variables are volatile as they may be accessed by ISRs.
 **************************************************************************/
volatile unsigned int blueDutyCycle = 0;
volatile unsigned int greenDutyCycle = 0;

// Function for PWM frequency setup
void setupTimerForSWPWM(void) {
    TA0CCTL2 = CCIE; // Enable interrupt for CCR2
    TA0CCR2 = 5;     // Interrupt frequency
}

// Function to set up GPIO for blue and green LEDs
void setupGPIO(void) {
    // Configure P1.5 as output for the blue LED and P1.6 for the green LED
    P1DIR |= BIT5 + BIT6 ;
    P1OUT &= ~(BIT5 + BIT6 ); // Initially off
}

// Function to set up PWM for red LED
void setupPWM(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    // Configure Red LED pin as output
    P1DIR |= BIT7;            // Red LED is connected to P1.7
    P1OUT &= ~(BIT7 );        // Initially off

    // Timer_A output mode for this pin
    P1SEL0 |= BIT7;           // Enable TA0.1 functionality on P1.7 for PWM output

    // Configure Timer_A
    TA0CTL = TASSEL_2 | MC_1; // Use SMCLK, up mode
    TA0CCR0 = 100;            // Set PWM Period

    // Initialise CCR1 for PWM, OUTMOD_7 for reset/set mode for the red LED
    TA0CCTL1 = OUTMOD_7;

    // Initial duty cycle for the red channel
    TA0CCR1 = 0;              // Initially off
}

// Function to set duty cycle for each LED (how 'bright' each colour is)
void setRGBDutyCycle(unsigned int redDuty, unsigned int greenDuty, unsigned int blueDuty) {
    // Update duty cycle for red LED (hardware PWM)
    TA0CCR1 = redDuty;

    // Update duty cycles for green and blue LEDs (software PWM)
    greenDutyCycle = greenDuty;
    blueDutyCycle = blueDuty;
}


