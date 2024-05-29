/**************************************************************************
 * Project Name: Exoplanet Detection Simulator
 * Module Name: lcd.c
 * Created on: 20 Feb 2024
 * Date Last Updated: 02/05/2024
 * Update Description:
 *    Changed D4 and D7 pins back to the original MSP430 pins connected.
 * Author: Finlay Harris
 **************************************************************************/

#include "lcd.h"
#include <msp430fr4133.h>

// Definitions for LCD pin connections on MSP430
#define LCD_RS BIT0 // P1.0 for RS
#define LCD_E  BIT1 // P1.1 for E
#define LCD_D4 BIT7 // P2.7 for D4
#define LCD_D5 BIT0 // P8.0 for D5
#define LCD_D6 BIT1 // P5.1 for D6
#define LCD_D7 BIT5 // P2.5 for D7

/**************************************************************************
 * Function: lcdInitGPIO
 **************************************************************************/
void lcdInitGPIO(void) {
    // Set LCD control and data pins as output
    P1DIR |= LCD_RS + LCD_E;
    P2DIR |= LCD_D4 + LCD_D7; // Pins on port 2
    P8DIR |= LCD_D5;          // Pin on port 8
    P5DIR |= LCD_D6;          // Pin on port 5

    // Initialise all control and data lines to low
    P1OUT &= ~(LCD_RS + LCD_E);
    P2OUT &= ~(LCD_D4 + LCD_D7);
    P8OUT &= ~LCD_D5;
    P5OUT &= ~LCD_D6;
}

/**************************************************************************
 * Function: lcdInit
 **************************************************************************/
void lcdInit(void) {
    lcdInitGPIO();          // Initialise GPIO for LCD

    __delay_cycles(20000);  // Initial delay for LCD power up

    // Start of sequence to initialise LCD in 4-bit mode
    lcdSendNibble(0x03, 1); // Initial commands to set interface length
    __delay_cycles(5000);
    lcdSendNibble(0x03, 1);
    __delay_cycles(1000);
    lcdSendNibble(0x03, 1);
    __delay_cycles(1000);
    lcdSendNibble(0x02, 1); // Set to 4-bit interface

    // Configuration commands in 4-bit mode
    lcdWriteByte(0x28, 1);  // Function set: 4-bit/2-line
    lcdWriteByte(0x0C, 1);  // Display ON; Cursor OFF, Blink OFF
    lcdWriteByte(0x06, 1);  // Entry mode: Increment & no shift
    lcdWriteByte(0x01, 1);  // Clear display
    __delay_cycles(3000);   // Delay for clear command
}

/**************************************************************************
 * Function: lcdSendNibble
 **************************************************************************/
void lcdSendNibble(unsigned char nibble, int isCommand) {
    if (isCommand) {
        P1OUT &= ~LCD_RS; // Command mode
    } else {
        P1OUT |= LCD_RS;  // Data mode
    }

    P2OUT = (P2OUT & ~(LCD_D4 | LCD_D7)) | ((nibble & 0x01) ? LCD_D4 : 0) | ((nibble & 0x08) ? LCD_D7 : 0);
    P8OUT = (P8OUT & ~LCD_D5) | ((nibble & 0x02) ? LCD_D5 : 0);
    P5OUT = (P5OUT & ~LCD_D6) | ((nibble & 0x04) ? LCD_D6 : 0);

    P1OUT |= LCD_E;         // Enable high
    __delay_cycles(2000);   // Pulse width
    P1OUT &= ~LCD_E;        // Enable low
}

/**************************************************************************
 * Function: lcdWriteByte
 **************************************************************************/
void lcdWriteByte(unsigned char byte, int isCommand) {
    lcdSendNibble(byte >> 4, isCommand);   // High nibble
    lcdSendNibble(byte & 0x0F, isCommand); // Low nibble
}

/**************************************************************************
 * Function: lcdSendCommand
 **************************************************************************/
void lcdSendCommand(unsigned char command) {
    lcdWriteByte(command, 1); // 1 indicates this is a command
}


/**************************************************************************
 * Function: lcdDisplayText
 **************************************************************************/
void lcdDisplayText(char *line1, char *line2) {
    lcdSendCommand(0x01); // Clear display command
    __delay_cycles(2000); // Delay for clear command to be processed

    // Set cursor to the beginning of the first line
    lcdSendCommand(0x80);
    while (*line1) {
        lcdWriteByte(*line1++, 0); // Write characters of line 1
    }

    // Set cursor to the beginning of the second line
    lcdSendCommand(0xC0);
    while (*line2) {
        lcdWriteByte(*line2++, 0); // Write characters of line 2
    }
}





