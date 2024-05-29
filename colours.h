/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: colours.h
 * Created on: 13 Feb 2024
 * Date Last Updated: 13/05/2024
 * Update Description:
 *    Defined the Colour structure and declared various predefined RGB colours.
 * Author: Finlay Harris
 **************************************************************************/

#ifndef COLOURS_H
#define COLOURS_H

#include "pwm.h" // Include PWM header

/**************************************************************************
 * Structure: Colour
 * Description:
 *    Defines an RGB colour structure. This structure is used to represent
 *    the RGB values of a colour where each field (red, green, blue) corresponds
 *    to the intensity values for the respective LEDs.
 * Fields:
 *    red - Red intensity
 *    green - Green intensity
 *    blue - Blue intensity
 **************************************************************************/
typedef struct {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
} Colour;

/**************************************************************************
 * Global Constants:
 * Description:
 *    Predefined colours as global constants. These are commonly used colours
 *    throughout the project, defined for easy access.
 **************************************************************************/
extern const Colour lilac;
extern const Colour purple;
extern const Colour lightBlue;
extern const Colour nBlue;
extern const Colour cyan;
extern const Colour turquoise;
extern const Colour nGreen;
extern const Colour limeGreen;
extern const Colour yellow;
extern const Colour orange;
extern const Colour pink;
extern const Colour nRed;
extern const Colour off;

/**************************************************************************
 * Function: setColour
 * Description:
 *    Sets the RGB LEDs to the specified colour by adjusting the PWM duty
 *    cycle for each colour component.
 * Parameters:
 *    colour - A pointer to the Colour structure that specifies the RGB values
 *             to be set for the LEDs.
 **************************************************************************/
void setColour(const Colour *colour);

#endif /* COLOURS_H */
