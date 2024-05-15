/*
 * File: SetSevenSegDisp.c
 *
 * Details: Shows the decimal number on the first four seven-segment
 * displays and a smiley face on the last two displays.
 *
 * Author: Yuehan You
 *
 */

// Header inclusion
#include "SetSevenSegDisp.h"

// The base addresses of the seven-segment display peripherals.
volatile unsigned char *SevenSegPtrLow = (unsigned char*) 0xFF200020;
volatile unsigned char *SevenSegPtrHigh = (unsigned char*) 0xFF200030;

//
// Function: InitialiseSevenSeg
// Default: Initialises seven-segment displays with default values.
// Arguments: Void.
// Return: Void.
//
void InitialiseSevenSeg() {

	// Display 0000 on first four displays
	SevenSegPtrLow[0] = 0x3F; // HEX0
	SevenSegPtrLow[1] = 0x3F; // HEX1
	SevenSegPtrLow[2] = 0x3F; // HEX2
	SevenSegPtrLow[3] = 0x3F; // HEX3

	// Display smiley face |_''_| on last two displays
	SevenSegPtrHigh[0] = 0x2C; // HEX4
	SevenSegPtrHigh[1] = 0x1A; // HEX5

}

//
// Function: SetSingleSevenSeg
// Details: Displays a digit on a particular seven-segment display
// Arguments: Seven-segment HEX number, single digit number to display
// Return: Void.
//
void SetSingleSevenSeg(uint8_t Disp, uint8_t Num) {

	// Mapping number to seven-segment display bits
	unsigned char SegBits = 0x00;

	switch(Num)
	{
		case 0x00: SegBits = 0x3F; break;
		case 0x01: SegBits = 0x06; break;
		case 0x02: SegBits = 0x5B; break;
		case 0x03: SegBits = 0x4F; break;
		case 0x04: SegBits = 0x66; break;
		case 0x05: SegBits = 0x6D; break;
		case 0x06: SegBits = 0x7D; break;
		case 0x07: SegBits = 0x07; break;
		case 0x08: SegBits = 0x7F; break;
		case 0x09: SegBits = 0x6F; break;
		case 0x0A: SegBits = 0x77; break;
		case 0x0B: SegBits = 0x7C; break;
		case 0x0C: SegBits = 0x39; break;
		case 0x0D: SegBits = 0x5E; break;
		case 0x0E: SegBits = 0x79; break;
		case 0x0F: SegBits = 0x71; break;
		default:   SegBits = 0x40; break;
	}

	// Writing it to the seven segment peripherals
	SevenSegPtrLow[Disp] = SegBits;
}

//
// Function: SetSevenSegDisp
// Details: Displays a four digit number on first four seven-segment display
// Arguments: Four digit number to display
// Return: Void.
//
void SetSevenSegDisp(uint16_t Num) {

	// To store each of the four digits in the number
	uint8_t Disp0, Disp1, Disp2, Disp3;

	// Digit at units place
	Disp0 = Num%10;

	// Digit at tens place
	Num = Num/10;
	Disp1 = Num%10;

	// Digit at hundredth place
	Num = Num/10;
	Disp2 = Num%10;

	// Digit at thousands place
	Num = Num/10;
	Disp3 = Num%10;

	// Writing it to the seven segment display 0
	SetSingleSevenSeg(0,Disp0);

	// Writing it to the seven segment display 1
	SetSingleSevenSeg(1,Disp1);

	// Writing it to the seven segment display 2
	SetSingleSevenSeg(2,Disp2);

	// Writing it to the seven segment display 3
	SetSingleSevenSeg(3,Disp3);

}
