/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: pwm.h
 * Created on: 13 Feb 2024
 * Date Last Updated: 13/02/2024
 * Update Description:
 *    Added setRGBDutyCycle() function to control RGB LED duty cycles more
 *    precisely via software PWM.
 * Author: Finlay Harris
 **************************************************************************/

#ifndef PWM_H
#define PWM_H

#include <msp430fr4133.h>

/**************************************************************************
 * External variables for duty cycles of RGB LEDs. These variables are used
 * to manage the PWM duty cycle for blue and green LEDs.
 **************************************************************************/
extern volatile unsigned int blueDutyCycle;
extern volatile unsigned int greenDutyCycle;

/**************************************************************************
 * Function: setupTimerForSWPWM
 * Description:
 *    Configures the timer used for software PWM. This setup includes
 *    timer period, mode, and interrupts.
 **************************************************************************/
void setupTimerForSWPWM(void);

/**************************************************************************
 * Function: setupGPIO
 * Description:
 *    Initialises GPIO settings for PWM functionality.
 *    This sets the direction and initial state of pins.
 **************************************************************************/
void setupGPIO(void);

/**************************************************************************
 * Function: setupPWM
 * Description:
 *    Initialises hardware PWM settings, including configuration of PWM
 *    registers and enabling PWM outputs on specific pins.
 **************************************************************************/
void setupPWM(void);

/**************************************************************************
 * Function: setRGBDutyCycle
 * Description:
 *    Sets the duty cycles for the RGB LEDs connected to PWM outputs.
 *    Allows independent control of each colour's brightness.
 * Parameters:
 *    redDuty - Duty cycle for the red LED
 *    greenDuty - Duty cycle for the green LED
 *    blueDuty - Duty cycle for the blue LED
 **************************************************************************/
void setRGBDutyCycle(unsigned int redDuty, unsigned int greenDuty, unsigned int blueDuty);

#endif /* PWM_H */
