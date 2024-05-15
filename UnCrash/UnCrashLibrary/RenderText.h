/*
 * File: RenderText.h
 *
 * Details: Displays score and game replay instructions text on LT24.
 *
 * Author: Santosh K S
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef RENDERTEXT_H_
#define RENDERTEXT_H_

// Header inclusions
#include <stdio.h> // Standard input/output library
#include <string.h> // For string related functions
#include <ctype.h> // To check and map characters

// Driver library
#include "DE1SoC_LT24/DE1SoC_LT24.h" // Driver for the LT24 Display Controller

// UnCrash library
#include "RenderWorld.h" // Renders game world
#include "CheckCollision.h" // Checks for collision between car and object
#include "Font.h" // Contains font data

//
// Structure: TextFormat
// Details: Sets the text size, colour and position
//
typedef struct TextFormat {
	uint8_t Scale;		// Text will be scaled by this number
	int16_t PosX;		// Text left-X position
	int16_t PosY;		// Text	top-Y position
	uint16_t Colour;	// RGB565 font colour
	int16_t LcPosX;		// Left-x position of the last character rendered
	int16_t LcPosY;		// Top-y position of the last character rendered
} TextFormat;

//
// Function: RenderText
// Details: Renders Text with the given text format on LT24.
// Arguments: Text string, text length, text format, and LT24 driver context
// Return: Void. Sets the last text's end X-Y position in the argument TextFormat.
//
void RenderText(char Text[], uint8_t TxtLen, TextFormat *Style, PLT24Ctx_t lt24);

//
// Function: SetScreenText
// Details: The text format to display after game ends
// Arguments: Score value, and LT24 driver context
// Return: Void.
//
void SetScreenText(uint16_t Score, PLT24Ctx_t lt24);

#endif /* RENDERTEXT_H_ */
