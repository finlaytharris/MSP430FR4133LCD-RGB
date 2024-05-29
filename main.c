/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: main
 * Created on: 12 Feb 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Changed colour & light sensor button pins.
 * Author: Finlay Harris
 **************************************************************************/

// Include necessary header files & libraries
#include "GasSpectra.h"
#include "colours.h"
#include "pwm.h"
#include "lcd.h"
#include "colourSensor.h"
#include "lightIntensity.h"
#include <msp430fr4133.h>
#include<stdio.h>
#include<string.h>

/**************************************************************************
 * Functions to intilise all system elements & buttons correctly
 **************************************************************************/
void initialiseSystem(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable GPIO power-on default high-impedance mode

    setupGPIO();               // Setup GPIO for LEDs
    setupPWM();                // Setup PWM for LEDs
    setupTimerForSWPWM();      // Setup software PWM time control
}

void initLightButton(void) {
    P5DIR &= ~BIT0;            // Set P5.0 as input
    P5REN |= BIT0;             // Enable pull-up/pull-down resistor
    P5OUT |= BIT0;             // Select pull-up mode

}

void initialiseRGBButton(void) {
    P5DIR &= ~BIT2;            // Set P5.2 to input
    P5REN |= BIT2;             // Enable pull-up/pull-down resistor
    P5OUT |= BIT2;             // Select pull-up mode
}

void initialiseColourSensorButton(void) {
    P5DIR &= ~BIT3;            // Set P5.3 as input
    P5REN |= BIT3;             // Enable pull-up/pull-down resistor
    P5OUT |= BIT3;             // Select pull-up mode

}

/**************************************************************************
 * Functions to test if buttons are pressed
 * Returns 1 if button is pressed (active low)
 **************************************************************************/
int isLightButtonPressed(void) {
    return (P5IN & BIT0) == 0;
}

int isRGBButtonPressed(void) {
    return (P5IN & BIT2) == 0;
}

int isColourSensorButtonPressed(void) {
    return (P5IN & BIT3) == 0;
}

/**************************************************************************
 * Functions to check if detected is white, red or blue.
 **************************************************************************/
int isDetectedColorValid() {
    char* detectedColor = Identify_Colour();        // Get the detected colour as a string
    return strcmp(detectedColor, "White") == 0 ||
           strcmp(detectedColor, "Red") == 0 ||
           strcmp(detectedColor, "Blue") == 0;
}

/**************************************************************************
 * Functions to check if light intensity is below threshold.
 **************************************************************************/
int isLightIntensityBelowThreshold(unsigned int threshold) {
    initADC();                                         // Initialise ADC for the light sensor
    unsigned int adcValue = blockingReadADC();         // Read ADC value using the blocking function
    int percentage = adcValueToPercentage(adcValue, 3, 75); // Convert ADC value to percentage

    return percentage < threshold;                     // Return true if light intensity is below threshold
}

/**************************************************************************
 * Main Function
 **************************************************************************/
int main(void) {
    // Initlising entire system - GPIO,PWM, buttons, LCD, ADC
    initialiseSystem();                      // Setup system, GPIO, PWM
    initLightButton();                       // Initialise the button
    initialiseRGBButton();
    initialiseColourSensorButton();
    lcdInit();                              // Initialise the LCD
    initADC();                              // Initialise ADC for the light sensor

    // Defining constant values for ADC
    unsigned const int minADCValue = 3;     // Minimum possible ADC value
    unsigned const int maxADCValue = 150;    // Maximum possible ADC value

    // Enable global interrupts
    _bis_SR_register(GIE);
    lcdDisplayText("Emission", " Spectrum 1");


    // Loop to check when buttons are pressed
        while(1) {

            // Check if the RGB button is pressed
            // If pressed display text on LCD...
            // ... & show colours on RGB...
            // ... only if a ' planet is found '
            // AKA- the light intensity is below 100 or red,blue or white is sensed
            // Otherwise display no planet found
            // This is simply a sequence of different gas spectrums shown using the RGB when a planet is found

            if (isRGBButtonPressed()) {
                //if (isLightIntensityBelowThreshold(100) && isDetectedColorValid()) {
                        lcdDisplayText("Emission", " Spectrum 1");
                        __delay_cycles(50000);
                        displayGasSpectrum("Hydrogen");
                        setColour(&off);

                        lcdDisplayText("Emission", " Spectrum 2");
                        __delay_cycles(50000);
                        displayGasSpectrum("Helium");
                        setColour(&off);

                        lcdDisplayText("Emission", " Spectrum 3");
                        __delay_cycles(50000);
                        displayGasSpectrum("Nitrogen");
                        setColour(&off);
                        lcdDisplayText("", "");
                    } else {
                        lcdDisplayText("No Planet", "Found");
                        __delay_cycles(50000);
                        setColour(&off);

                   // }

            }



            // Check if the Colour Sensor button is pressed
            // If pressed display text on878\ LCD...
            // ... & call colour detection function
            // Determine colour sensed via function
            // Display colour name on LCD
            // This is simply detecting & identifying the colour sensed, the displaying it
            if (isColourSensorButtonPressed()) {
                initialiseColourSensor();                                 // Initialise colour sensor
                __delay_cycles(10000);                                    // Debounce delay
                if (isColourSensorButtonPressed()) {
                    while (isColourSensorButtonPressed());                // Wait for release
                    lcdDisplayText("Observing", "Colour");
                    Colour_Detect();                                      // Perform colour detection
                    char* detectedColour = Identify_Colour();             // Get the detected colour as a string
                    lcdDisplayText("Detected Colour:", detectedColour);   // Display the detected colour on the LCD
                }
            }

            // Check if the Light Sensor button is pressed
            // If pressed initlise ADC and start conversion...
            // ... & read ADC value read
            // Convert ADC value into a percentage
            // Display percentage on LCD
            // This is simply detecting & converting the light intensity (voltage)...
            // ... to an ADC value, mapping it to a percentage and displaying it.
            if (isLightButtonPressed()) {
                initADC();                                                                              // Initialise ADC only after button is pressed
                ADCCTL0 |= ADCENC | ADCSC;                                                              // Enable and start conversion
                   // Wait until the button is released
                   while(isLightButtonPressed()) {
                      // Read the voltage value & Convert to digital signal
                       unsigned int adcValue = blockingReadADC();
                       // Convert to percentage
                       int percentage = adcValueToPercentage(adcValue, minADCValue, maxADCValue);
                       // Convert percentage int to string
                       char displayBuffer[32];                                                          // Define a buffer large enough to hold formatted string
                       sprintf(displayBuffer, " %d%%", percentage);                                     // Format the string with the percentage value
                       lcdDisplayText("Light Itensity:",displayBuffer);                                 // Pass the formatted string to your display function
                   }

               }

        }


    return 0;
}

/**************************************************************************
 * Function Name: Timer_A_ISR
 * Description:
 *    Interrupt Service Routine for Timer A. It manages PWM for the LEDs
 *    by adjusting the duty cycle based on a software PWM approach. This
 *    ISR handles the Compare/Capture Interrupt for CCR2. PWM for Blue
 *    and Green LEDs are adjusted within this interrupt.
 **************************************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A_ISR(void) {
    switch(__even_in_range(TA0IV, TA0IV_TAIFG)) {
        case TA0IV_TACCR2: {                             // Handle CCR1 interrupt
            static unsigned int pwmCount = 0;
            pwmCount = (pwmCount + 1) % 256;

            // Software PWM for Blue LED
            if (pwmCount < blueDutyCycle) P1OUT |= BIT5; // BIT5 for blue LED
            else P1OUT &= ~BIT5;

            // Software PWM for Green LED
            if (pwmCount < greenDutyCycle) P1OUT |= BIT6; // BIT6 for green LED
            else P1OUT &= ~BIT6;

            break;
        }
    }
}

/**************************************************************************
 * Function Name: ADC_ISR
 * Description:
 *    Interrupt Service Routine for the ADC. This ISR handles the ADC
 *    interrupt flag and reads the result from the ADC memory. The result
 *    is stored in adcResult. It also clears the ADC interrupt flag to
 *    prepare for the next ADC operation.
 **************************************************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    unsigned int adcResult;

    switch(__even_in_range(ADCIV, ADCIV_ADCIFG)) {
        case ADCIV_ADCIFG:                           // ADC Interrupt Flag
            adcResult = ADCMEM0;

            // Clear the interrupt flag
            ADCIFG &= ~ADCIFG0;
            break;
    }
}







