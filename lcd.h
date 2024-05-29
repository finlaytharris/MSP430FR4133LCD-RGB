/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: lcd.h
 * Created on: 20 Feb 2024
 * Date Last Updated: 03/03/2024
 * Update Description:
 *    Modified lcdDisplayText() to support displaying two strings, allowing
 *    text to be set separately on each line of the LCD.
 * Author: Finlay Harris
 **************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/**************************************************************************
 * Function: lcdInitGPIO
 * Description:
 *    Initialises GPIO pins connected to the LCD for output. This includes
 *    both control and data lines. Ensures all lines are set to a known low
 *    state initially.
 **************************************************************************/
void lcdInitGPIO(void);

/**************************************************************************
 * Function: lcdInit
 * Description:
 *    Performs the initial setup of the LCD display after powering up.
 *    This function is critical in setting the LCD to operate in 4-bit mode
 *    and configuring display characteristics like display mode and cursor
 *    settings.
 **************************************************************************/
void lcdInit(void);

/**************************************************************************
 * Function: lcdSendNibble
 * Description:
 *    Sends a 4-bit nibble to the LCD, used in both command and data mode.
 * Parameters:
 *    nibble - 4-bit data to send
 *    isCommand - Indicates if the nibble is part of a command (1) or data (0)
 **************************************************************************/
void lcdSendNibble(unsigned char nibble, int isCommand);

/**************************************************************************
 * Function: lcdWriteByte
 * Description:
 *    Sends a full byte to the LCD by splitting it into two nibbles. This function
 *    is used for both sending commands and writing display data.
 * Parameters:
 *    byte - The byte to send to the LCD.
 *    isCommand - Indicator if the byte is a command or data.
 **************************************************************************/
void lcdWriteByte(unsigned char byte, int isCommand);

/**************************************************************************
 * Function: lcdSendCommand
 * Description:
 *    Sends a command byte to the LCD to perform various display functions.
 *    This function utilises the lcdWriteByte function to send the command.
 * Parameters:
 *    command - The command byte to send to the LCD.
 **************************************************************************/
void lcdSendCommand(unsigned char command);

/**************************************************************************
 * Function: lcdDisplayText
 * Description:
 *    Displays specified text on the LCD. The function clears the display
 *    first, then positions the cursor and writes the provided strings
 *    to the first and second line.
 * Parameters:
 *    line1 - Text to display on the first line.
 *    line2 - Text to display on the second line.
 **************************************************************************/
void lcdDisplayText(char *line1, char *line2);

#endif /* LCD_H_ */
