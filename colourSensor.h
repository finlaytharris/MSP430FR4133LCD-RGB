/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: colourSensor.c
 * Created on: 15 March 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Modified red,blue,green coeffs to not be a constant.
 * Author: Tingwan Liu (primary author) & Finlay Harris
 **************************************************************************/
#ifndef COLOURSENSOR_H_
#define COLOURSENSOR_H_

#include <msp430fr4133.h>
#include <intrinsics.h>

// Macros for time delays using the specified crystal frequency
#define XTAL   4  // Crystal frequency in MHz
#define delay_us(x) __delay_cycles((unsigned long)(((unsigned long)x) * XTAL))         // Microsecond delay
#define delay_ms(x) __delay_cycles((unsigned long)(((unsigned long)x) * XTAL * 1000))  // Millisecond delay
#define delay_s(x)  __delay_cycles((unsigned long)(((unsigned long)x) * XTAL * 1000000)) // Second delay


// Declaration of global variables used in color detection
extern unsigned int pulses_num;          // Count of pulses from the colour sensor
extern unsigned char timer_10ms_cnt;     // Counter for timing events
extern unsigned char colour_det_flag;    // Flag to control detection process
extern float red_coeff;                  // Coefficient for red colour calculations
extern float green_coeff;                // Coefficient for green colour calculations
extern float blue_coeff;                 // Coefficient for blue colour calculations
extern unsigned int red_val;             // Calculated intensity of red colour
extern unsigned int green_val;           // Calculated intensity of green colour
extern unsigned int blue_val;            // Calculated intensity of blue colour


/**************************************************************************
 * Function: initialiseColourSensor
 * Description:
 *    Configures the GPIO and interrupt settings necessary for the operation
 *    of the colour sensor. This includes setting up the sensor input pin
 *    and the control outputs for the LEDs used in color detection.
 **************************************************************************/
void initialiseColourSensor(void);

/**************************************************************************
 * Function: Colour_Detect
 * Description:
 *    Executes the sequence for detecting colours using the RGB LEDs.
 *    It controls the LEDs to emit specific colours and measures the response
 *    from the colour sensor to determine the reflected colour.
 **************************************************************************/
void Colour_Detect(void);

/**************************************************************************
 * Function: Identify_Colour
 * Description:
 *    Analyses the RGB values obtained from Colour_Detect function to determine
 *    the most prominent colour detected. Uses a simple threshold mechanism to
 *    differentiate among predefined colours.
 * Returns:
 *    A string literal indicating the identified colour: "Red", "Blue", "White",
 *    or "Unknown" if no clear colour match is found.
 **************************************************************************/
char* Identify_Colour(void);

#endif /* COLOURSENSOR_H_ */
