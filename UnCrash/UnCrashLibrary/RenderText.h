/*
 * File: RenderText.c
 *
 * Details : Declaration of functions that render text on LT24
 *
 */


#ifndef RENDERTEXT_H_
#define RENDERTEXT_H_

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "Font.h"
#include "string.h"
#include "ctype.h"
//
// Sets the text size, colour and position
//
typedef struct TextFormat {
	uint8_t Scale;		// text will be scaled by this number
	int16_t PosX;		// text left-X position
	int16_t PosY;		// text	top-Y position
	uint16_t Colour;	// RGB565 font colour
	bool Wrap;			// Wraps the text to next line if it goes out of bounds
	int16_t LcPosX;		// left-x position of the last character rendered
	int16_t LcPosY;		// top-y position of the last character rendered
} TextFormat;


void SetScreenText(PLT24Ctx_t lt24);

#endif /* RENDERTEXT_H_ */
