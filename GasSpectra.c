/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: GasSpectra.c
 * Created on: 12 Feb 2024
 * Date Last Updated: 06/05/2024
 * Update Description:
 *    Defined more gas spectrums.
 * Author: Finlay Harris
 **************************************************************************/

#include "GasSpectra.h"
#include "colours.h"
#include<string.h>

/**************************************************************************
 * Array of GasSpectrum structures containing the spectral colour sequences
 * for different gases.
 * Each GasSpectrum entry contains a gas name and an array of pointers
 * to Colour structures representing the gas's emission
 * spectrum, followed by the count of colours in the spectrum.
 **************************************************************************/
GasSpectrum gasSpectra[] = {
           {"Hydrogen", {&purple, &nBlue, &cyan, &nRed}, 4},
           {"Helium", {&purple, &nBlue, &lightBlue, &cyan, &turquoise, &nGreen, &yellow, &orange, &nRed}, 9},
           {"Nitrogen", {&purple, &turquoise, &nGreen, &limeGreen, &yellow, &orange, &nRed}, 7}
//           {"Carbon Dioxide", {&nRed, &orange, &yellow, &green, &blue}, 5},
//           {"Methane", {&nBlue, &nGreen, &yellow, &orange, &red}, 5},
//           {"Ozone", {&lightBlue, &nBlue, &purple, &lilac}, 4}
//           {"Argon", {&lightBlue, &blue, &nBlue}, 3},
//           {"Sulfur Dioxide", {&yellow, &orange, &nRed, &purple}, 4}
};
const int gasSpectraSize = sizeof(gasSpectra) / sizeof(GasSpectrum);

// Function Definition of gas spectrum displays
void displayGasSpectrum(const char* gasName) {
    int i,j =0;
    for (i = 0; i < gasSpectraSize; i++) {
        if (strcmp(gasSpectra[i].name, gasName) == 0) {
            // Match found, display the LED colours in sequence
            for(j = 0; j < gasSpectra[i].numColours; j++) {
                setColour(gasSpectra[i].colours[j]);
                __delay_cycles(500000);             // Delay between colours
            }
            break;
        }
    }
}



