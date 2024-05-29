/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: colours.c
 * Created on: 13 Feb 2024
 * Date Last Updated: 13/02/2024
 * Update Description:
 *    Defined colour values & setColour Function.
 * Author: Finlay Harris
 **************************************************************************/

#include "colours.h"

// Define the predefined colours
const Colour lilac = {800, 20, 840};
const Colour purple  = {8000, 10, 255};
const Colour lightBlue   = {0, 50, 200};
const Colour nBlue  = {0, 0, 255};
const Colour cyan   = {0, 255, 255};
const Colour turquoise = {0, 255, 50};
const Colour nGreen = {0, 255, 0};
const Colour limeGreen = {5000, 190, 0};
const Colour yellow = {8000, 100, 0};
const Colour orange = {5000, 25, 0};
const Colour pink = {8000, 10, 200};
const Colour nRed = {255, 0, 0};
const Colour off = {0, 0, 0};


// Function to set a colour
void setColour(const Colour *colour) {
    setRGBDutyCycle(colour->red, colour->green, colour->blue);
}

