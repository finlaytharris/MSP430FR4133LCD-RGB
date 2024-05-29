/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: lightIntensity.c
 * Created on: 12 Feb 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Defined blockingReadADC function.
 * Author: Finlay Harris
 **************************************************************************/

#include "lightIntensity.h"

#define LIGHT_SENSOR_PIN BIT4
#define ADC_CHANNEL INCH_4

// Phototransistor is connected to ADC pin P1.4
// Configure P1.4 for ADC input function

/**************************************************************************
 * Function: initADC
 **************************************************************************/
void initADC(void) {
    // Enable ADC input function on P1.4
    P1SEL0 |= BIT4;
    SYSCFG2 |= ADCPCTL4;              // Enable ADC function on the pin corresponding to P1.4

    // Configure ADC12
    ADCCTL0 = ADCSHT_2 | ADCON;       // Sample hold time and ADC on
    ADCCTL1 = ADCSHP;                 // Use sampling timer
    ADCCTL2 = ADCRES;                 // 10-bit conversion results
    ADCMCTL0 = ADCSREF_0 | ADCINCH_4; // Vref+ = AVCC and Vref- = AVSS, Input channel A4

    // Do not enable ADC conversion or interrupts here
}

/**************************************************************************
 * Function: startADC
 **************************************************************************/
void startADC(void) {
    ADCIE = ADCIE0;            // Enable ADC conversion complete interrupt
    ADCCTL0 |= ADCENC | ADCSC; // Enable and start conversion
}



/**************************************************************************
 * Function: blockingReadADC
 **************************************************************************/
unsigned int blockingReadADC(void) {
    ADCCTL0 |= ADCENC | ADCSC;        // Enable and start conversion

    while (!(ADCIFG & ADCIFG0));      // Wait for conversion to complete

    unsigned int adcResult = ADCMEM0; // Read the conversion result from the ADC memory register

    ADCIFG &= ~ADCIFG0;              // Clear the interrupt flag

    return adcResult;                // Return the ADC result
}


/**************************************************************************
 * Function: adcValueToPercentage
 **************************************************************************/
int adcValueToPercentage(unsigned int adcValue, unsigned int minADCValue, unsigned int maxADCValue) {
    if (adcValue < minADCValue) {
        return 0;    // Below the minimum value should be 0%
    } else if (adcValue > maxADCValue) {
        return 100;  // Above the maximum value should be 100%
    } else {
        // Calculate percentage in the range from minADCValue to maxADCValue
        return (int)(((long)(adcValue - minADCValue) * 100) / (maxADCValue - minADCValue));
    }
}

