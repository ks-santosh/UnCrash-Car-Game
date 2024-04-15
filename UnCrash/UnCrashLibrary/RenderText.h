/*
 * File: RenderText.c
 *
 * Details : Declaration of functions that render text on LT24
 *
 */

#ifndef RENDERTEXT_H_
#define RENDERTEXT_H_

#include <stdio.h>
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "RenderWorld.h"
#include "CheckCollision.h"
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
	int16_t LcPosX;		// left-x position of the last character rendered
	int16_t LcPosY;		// top-y position of the last character rendered
} TextFormat;

//
// Renders Text with the given format on LT24
//
void RenderText(char Text[], uint8_t TxtLen, TextFormat *Style, PLT24Ctx_t lt24);

//
// The text format to display after game ends
//
void SetScreenText(uint16_t Score, PLT24Ctx_t lt24);

#endif /* RENDERTEXT_H_ */
