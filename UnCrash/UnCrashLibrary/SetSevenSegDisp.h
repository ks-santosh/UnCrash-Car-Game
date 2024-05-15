/*
 * File: SetSevenSegDisp.h
 *
 * Details: Shows the decimal number on the first four seven-segment
 * displays and a smiley face on the last two displays.
 *
 * Author: Yuehan You
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef SEVENSEGDISP_H_
#define SEVENSEGDISP_H_

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

//
// Function: InitialiseSevenSeg
// Default: Initialises seven-segment displays with default values.
// Arguments: Void.
// Return: Void.
//
void InitialiseSevenSeg();

//
// Function: SetSingleSevenSeg
// Details: Displays a digit on a particular seven-segment display
// Arguments: Seven-segment HEX number, single digit number to display
// Return: Void.
//
void SetSingleSevenSeg(uint8_t Disp, uint8_t Num);

//
// Function: SetSevenSegDisp
// Details: Displays a four digit number on first four seven-segment display
// Arguments: Four digit number to display
// Return: Void.
//
void SetSevenSegDisp(uint16_t Num);

#endif /* SEVENSEGDISP_H_ */
