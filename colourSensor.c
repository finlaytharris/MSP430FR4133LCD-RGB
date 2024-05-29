/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: colourSensor.c
 * Created on: 15 March 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Modified ISRs.
 * Author: Tingwan Liu (primary author) & Finlay Harris
 **************************************************************************/

#include"lcd.h"
#include "colourSensor.h"


// Definition of global variables
unsigned int pulses_num = 0;
unsigned char timer_10ms_cnt = 0;
unsigned char colour_det_flag = 0;
float red_coeff = 4.7059;
float green_coeff = 4.9412;
float blue_coeff = 5.3333;
unsigned int red_val = 0;
unsigned int green_val = 0;
unsigned int blue_val = 0;

/**************************************************************************
 * Function: initialiseColourSensor
 **************************************************************************/
void initialiseColourSensor(void) {
    // Ensure LEDs are off
    P8DIR |= BIT2 | BIT3;    // Set P8.2 and P8.3 as output
    P8OUT &= ~(BIT2 | BIT3); // Turn off LEDs

    // Configure input from color sensor
    P1DIR &= ~BIT3;          // Set P1.3 as input
    P1REN |= BIT3;           // Enable pull-up resistor
    P1OUT |= BIT3;           // Set pull-up (modify based on your sensor output characteristics)
    P1IE |= BIT3;            // Enable interrupt on P1.3
    P1IES &= ~BIT3;          // Trigger on rising edge
    P1IFG &= ~BIT3;          // Clear interrupt flag

    // Enable interrupts
    __bis_SR_register(GIE);  // Ensure global interrupts are enabled
}


/**************************************************************************
 * Function: Colour_Detect
 **************************************************************************/
void Colour_Detect(void)
{
    // Turn off both LED outputs
    P8OUT &= ~(BIT2 + BIT3);
    delay_ms(100); // Ensure stable state

    // Initialize detection process
    red_val = green_val = blue_val = 0; // Reset values
    pulses_num = 0;                     // Reset pulse count
    colour_det_flag = 1;                 // Set flag to start detection

    // Enable interrupts just once at the start
    P1IE |= BIT3; // Enable interrupt on P1.3

    // Red measurement
    P8OUT |= (BIT2 | BIT3);           // Turn on LEDs for red measurement
    delay_ms(100);                    // Measurement period
    red_val = pulses_num / red_coeff; // Calculate red value
    if (red_val > 255) red_val = 255;

    // Reset for green measurement
    pulses_num = 0;                       // Reset pulse count
    P8OUT &= ~(BIT2);                     // Change LED state for green measurement
    P8OUT |= BIT3;
    delay_ms(100);                        // Measurement period
    green_val = pulses_num / green_coeff; // Calculate green value
    if (green_val > 255) green_val = 255;

    // Reset for blue measurement
    pulses_num = 0;                     // Reset pulse count
    P8OUT &= ~(BIT3);                   // Change LED state for blue measurement
    P8OUT |= BIT2;
    delay_ms(100);                      // Measurement period
    blue_val = pulses_num / blue_coeff; // Calculate blue value
    if (blue_val > 255) blue_val = 255;

    // Clean up
    P8OUT &= ~(BIT2 | BIT3); // Turn off LEDs
    P1IE &= ~BIT3;           // Disable interrupt to stop measurements

}

/**************************************************************************
 * Function: Identify_Colour
 **************************************************************************/
char* Identify_Colour(void) {
    unsigned int threshold = 100;
    if (red_val > threshold && green_val < threshold && blue_val < threshold) {
        return "Red";
    } else if (blue_val > threshold && red_val < threshold && green_val < threshold) {
        return "Blue";
    } else if (red_val > threshold && green_val > threshold && blue_val > threshold) {
        return "White";
    }
    return "Unknown";
}


/**************************************************************************
 * ISR: Port_1
 * Description:
 *    Interrupt Service Routine for PORT1_VECTOR that handles the colour
 *    sensor output interrupts on pin P1.3. It increments a pulse counter
 *    whenever the colour detection flag is set, allowing for measurement
 *    of colour intensity based on the frequency of the pulses received.
 **************************************************************************/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void) {
#endif
    if (P1IFG & BIT3) {  // Check if the interrupt is due to P1.3
        P1IFG &= ~BIT3;  // Clear the interrupt flag for P1.3
        if (colour_det_flag) {
            pulses_num++;
        }
    }
}



/**************************************************************************
 * ISR: Timer_A
 * Description:
 *    Interrupt Service Routine for TIMER0_A0_VECTOR that acts as a timing
 *    mechanism for the colour detection process. It increments a counter every
 *    10 ms, and after 1 second (100 counts), it resets the colour detection
 *    flag to stop the measurement process.
 **************************************************************************/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
#endif
{
    if (colour_det_flag) {
        timer_10ms_cnt++;
        if (timer_10ms_cnt > 99) {
            colour_det_flag = 0; // Resetting the detection flag to stop counting
            timer_10ms_cnt = 0;  // Reset timer count
            P1IE &= ~BIT3;       //  Disable further interrupts
        }
    }

}




