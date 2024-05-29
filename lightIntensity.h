/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: lightIntensity.h
 * Created on: 21 March 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Defined blockingReadADC function.
 * Author: Finlay Harris
 **************************************************************************/

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include <msp430fr4133.h>

/**************************************************************************
 * Function: initADC
 * Description:
 *    Initialises the ADC for reading light intensity from a phototransistor
 *    connected to P1.4. This function configures the ADC to use AVCC and AVSS
 *    as references and sets the sample and hold time.
 **************************************************************************/
void initADC(void);

/**************************************************************************
 * Function: startADC
 * Description:
 *    Starts the ADC conversion process by enabling ADC interrupts and
 *    starting the conversion. This setup allows for continuous reading
 *    as needed by enabling and starting the ADC converter.
 **************************************************************************/
void startADC(void);

/**************************************************************************
 * Function: blockingReadADC
 * Description:
 *    Performs a synchronous (blocking) read of the ADC. This function
 *    starts an ADC conversion and waits until it is complete, returning
 *    the result.
 * Returns:
 *    adcResult - The result of the ADC conversion.
 **************************************************************************/
unsigned int blockingReadADC(void);

/**************************************************************************
 * Function: adcValueToPercentage
 * Description:
 *    Converts an ADC value to a percentage relative to defined minimum and
 *    maximum values. This function provides a normalised output between 0%
 *    and 100% based on specified thresholds.
 * Parameters:
 *    adcValue - The ADC value to convert.
 *    minADCValue - The minimum ADC value corresponding to 0%.
 *    maxADCValue - The maximum ADC value corresponding to 100%.
 * Returns:
 *    The percentage representation of the adcValue.
 **************************************************************************/
int adcValueToPercentage(unsigned int adcValue, unsigned int minADCValue, unsigned int maxADCValue);

#endif /* LIGHTSENSOR_H_ */
