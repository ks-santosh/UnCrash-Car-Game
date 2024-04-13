/*
 * File: RenderText.c
 *
 * Details : Renders text on LT24
 *
 */
#include "RenderText.h"

//
// Renders Text with the given format on LT24
//
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

//
// The text format to display after game ends
//
void SetScreenText(uint16_t Score, PLT24Ctx_t lt24) {

	if(Score > 9999) {
		Score = 9999;
	}

	char TextCrash[] = "CRASH";
	TextFormat Style = {.Scale = 8, .PosX = 24, .PosY = 30, .Colour = 0xF800};

	if(Score < 9999) {
		RenderText(TextCrash, strlen(TextCrash), &Style, lt24);
	}
	else
	{
		char TextGameEnd[] = "GAME END";
		Style.Scale = 5;
		Style.PosX = 20;
		Style.Colour =  0x3667;
		RenderText(TextGameEnd, strlen(TextGameEnd), &Style, lt24);
	}

	char TextScore[] = "SCORE";
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20;
	Style.Scale = 8;
	Style.Colour = 0xFFE0;
	RenderText(TextScore, strlen(TextScore), &Style, lt24);

	char NumScore[4];
	sprintf(NumScore, "%d", Score);
	// calculate score x position to display in middle
	uint8_t ScoreWidth = 0;
	for(uint8_t i = 0; NumScore[i] != '\0'; i++) {
		ScoreWidth += DiWidth[NumScore[i]-'0']*Style.Scale + Style.Scale;
	}
	ScoreWidth -= Style.Scale; // remove trail space width
	Style.PosX = (LT24_WIDTH - ScoreWidth)/2;
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20;
	Style.Colour = 0xFD00;
	RenderText(NumScore, strlen(NumScore), &Style, lt24);

	char TextKeyPress[] = "PRESS KEY2 TO";
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20;
	Style.PosX = 23;
	Style.Scale = 3;
	Style.Colour = 0x3667;
	RenderText(TextKeyPress, strlen(TextKeyPress), &Style, lt24);

	char TextKeyNum[] = "2";
	Style.PosX = 23 + 46*Style.Scale;
	Style.Colour = 0xFFFF;
	RenderText(TextKeyNum, strlen(TextKeyNum), &Style, lt24);

	char TextRestart[] = "RESTART";
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20;
	Style.PosX = 30;
	Style.Scale = 5;
	Style.Colour = 0x3667;
	RenderText(TextRestart, strlen(TextRestart), &Style, lt24);

}
