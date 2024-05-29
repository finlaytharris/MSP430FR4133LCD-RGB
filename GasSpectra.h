/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: GasSpectra.h
 * Created on: 12 Feb 2024
 * Date Last Updated: 12/02/2024
 * Update Description:
 *    Initial creation of the header file for defining the GasSpectrum
 *    structure and the declaration of the displayGasSpectrum function.
 * Author: Finlay Harris
 **************************************************************************/

#ifndef GAS_SPECTRA_H
#define GAS_SPECTRA_H

#include "colours.h" // Include the colours header for Colour structure reference

/**************************************************************************
 * Structure: GasSpectrum
 * Description:
 *    Represents a gas emission spectrum. This structure is used to store
 *    the name of the gas and an array of colours representing its spectrum
 *    in the visible light range.
 * Members:
 *    name - The name of the gas.
 *    colours - An array of pointers to Colour structures, each representing
 *              a colour in the gas's emission spectrum.
 *    numColours - The number of colours in the spectrum.
 **************************************************************************/
typedef struct {
    const char* name;          // Name of the gas
    const Colour* colours[12]; // Array of pointers to Colour structures
    int numColours;            // Number of colours in the spectrum
} GasSpectrum;

/**************************************************************************
 * Function: displayGasSpectrum
 * Description:
 *    Displays the gas spectrum on an RGB LED. This function searches for
 *    a gas's name within an array of GasSpectrum structures and sequentially
 *    sets an RGB LED to each colour in the identified gas spectrum.
 * Parameters:
 *    gasName - The name of the gas whose spectrum is to be displayed.
 **************************************************************************/
void displayGasSpectrum(const char* gasName);

#endif /* GAS_SPECTRA_H */

