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
	uint8_t Scale = Style->Scale;

	const uint8_t *Letter;
	uint8_t CharIdx;
	uint8_t CharWidth;

	// loop through all characters
	for(uint8_t i = 0; i < TxtLen; i++) {
		// Get the char
		char TxtChar = toupper(Text[i]);

		// blank space
		if(TxtChar == 32){
			PosX = PosX + FONT_HEIGHT * Scale;
			continue;
		}

		if((TxtChar >= 'A') && (TxtChar <= 'Z')) {
			CharIdx = TxtChar-'A';
			Letter = &Alphabet[CharIdx][0];
			CharWidth = AlWidth[CharIdx];
		}
		else if((TxtChar >= '0') && (TxtChar <= '9')) {
			CharIdx = TxtChar-'0';
			Letter = &Digits[CharIdx][0];
			CharWidth = DiWidth[CharIdx];
		}
		else {
			continue;
		}

		// iterate through columns and rows of pixel
		for(uint8_t c = 0; c < CharWidth; c++) {

			for(uint8_t r = 0; r < FONT_HEIGHT; r++) {

				// if pixel is 0 (black)
				if(! *(Letter + c + CharWidth * r)) {
					LT24_drawColourWindow(lt24, Style->Colour, PosX+c*Scale, PosY+r*Scale, Scale, Scale);
				}
			}
		}

		PosX = PosX + CharWidth*Scale + Scale;
	}

	Style->LcPosX = PosX;
	Style->LcPosY = PosY;
}

void SetScreenText(PLT24Ctx_t lt24) {
	char TextCrash[] = "CRASH0123";
	TextFormat Style = {.Scale = 5, .PosX = 24, .PosY = 160, .Colour = 0xF800, .Wrap = false};
	RenderText(TextCrash, strlen(TextCrash), &Style, lt24);
}
