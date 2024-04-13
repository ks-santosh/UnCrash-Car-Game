/*
 * File: RenderText.c
 *
 * Details : Renders text on LT24
 *
 */
#include "RenderText.h"

void RenderText(char Text[], uint8_t TxtLen, TextFormat *Style, PLT24Ctx_t lt24) {

	// Local Variables
	int16_t PosX = Style->PosX;
	int16_t PosY = Style->PosY;

	const uint8_t *Letter;

	// loop through all characters
	for(uint8_t i = 0; i < TxtLen; i++) {
		// Get the char
		char TxtChar = toupper(Text[i]);

		// blank space
		if(TxtChar == 32){
			PosX = PosX + 5;
			continue;
		}

		uint8_t CharIdx = TxtChar-'A';

		Letter = &Alphabet[TxtChar-'A'][0];

		// iterate through columns and rows of pixel
		for(uint8_t c = 0; c < AlWidth[CharIdx]; c++) {

			for(uint8_t r = 0; r < 5; r++) {

				// if pixel is 0 (black)
				if(! *(Letter + c + AlWidth[CharIdx] * r)) {
					LT24_drawPixel(lt24, Style->Colour, PosX+c, PosY+r);
				}
			}
		}

		PosX = PosX + AlWidth[CharIdx] + 1;
	}
}

void SetScreenText(PLT24Ctx_t lt24) {
	char Text[] = "hello world";
	TextFormat Style = {.Scale = 1, .PosX = 120, .PosY = 160, .Colour = 0xF800, .Wrap = false};
	RenderText(Text, strlen(Text), &Style, lt24);
}
