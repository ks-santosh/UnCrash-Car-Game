/*
 * File: RenderText.c
 *
 * Details: Displays score and game replay instructions text on LT24.
 *
 * Author: Santosh K S
 *
 */

// Header inclusion
#include "RenderText.h"

//
// Function: RenderText
// Details: Renders Text with the given text format on LT24.
// Arguments: Text string, text length, text format, and LT24 driver context
// Return: Void. Sets the last text's end X-Y position in the argument TextFormat.
//
void RenderText(char Text[], uint8_t TxtLen, TextFormat *Style, PLT24Ctx_t lt24) {

	// Local Variables
	int16_t PosX = Style->PosX; // Text starting x position
	int16_t PosY = Style->PosY; // Text starting y position
	uint8_t Scale = Style->Scale; // Text scaling value

	const uint8_t *Letter; // Pointer the the pixel array of the character

	uint8_t CharIdx; // Character array index
	uint8_t CharWidth; // Character's pixel width

	// Loop through all characters in the text
	for(uint8_t i = 0; i < TxtLen; i++) {

		// Get the upper-case character
		char TxtChar = toupper(Text[i]);

		// If character is blank space
		if(TxtChar == 32){

			PosX = PosX + FONT_HEIGHT * Scale; // Leave horizontal space
			continue; // Continue with next character
		}

		// If character is an alphabet
		if((TxtChar >= 'A') && (TxtChar <= 'Z')) {

			CharIdx = TxtChar-'A'; // Get the character array index
			Letter = &Alphabet[CharIdx][0]; // Pointer the the pixel array of the character
			CharWidth = AlWidth[CharIdx]; // Character's pixel width
		}
		// Else if the character is a number
		else if((TxtChar >= '0') && (TxtChar <= '9')) {

			CharIdx = TxtChar-'0'; // Get the digit's array index
			Letter = &Digits[CharIdx][0]; // Pointer the the pixel array of the digit
			CharWidth = DiWidth[CharIdx]; // Digit's pixel width
		}
		// Else unknown character
		else {

			continue; // Continue with the next character
		}

		// Iterate through columns and rows of pixel of the characters
		// Iterate from 0 to pixel width of the character
		for(uint8_t c = 0; c < CharWidth; c++) {

			// Iterate from 0 to font height of the character
			for(uint8_t r = 0; r < FONT_HEIGHT; r++) {

				// If pixel is 0 (black) at the position
				if(! *(Letter + c + CharWidth * r)) {

					// Draw black pixel box starting from the particular row and column on LT24
					// The size of the pixel box is set in font scaling variable
					LT24_drawColourWindow(lt24, Style->Colour, PosX+c*Scale, PosY+r*Scale, Scale, Scale);
				}
			}
		}

		// After displaying each charachter leave space according to font scale factor
		PosX = PosX + CharWidth*Scale + Scale;
	}

	// Update the last character X-Y position
	Style->LcPosX = PosX;
	Style->LcPosY = PosY;
}

//
// Function: SetScreenText
// Details: The text format to display after game ends
// Arguments: Score value, and LT24 driver context
// Return: Void.
//
void SetScreenText(uint16_t Score, PLT24Ctx_t lt24) {

	// If score greater than max score
	if(Score > MAX_SCORE) {
		Score = MAX_SCORE; // Set the score to max value
	}

	char TextCrash[] = "CRASH";
	// Set the text format for displaying crash status
	TextFormat Style = {.Scale = 8, .PosX = 24, .PosY = 30, .Colour = 0xF800};

	// If score is less than max then game ended due to crash
	if(Score < MAX_SCORE) {

		// Display CRASH on LT24
		RenderText(TextCrash, strlen(TextCrash), &Style, lt24);
	}
	// Else game completed, achieving maximum score
	else
	{
		char TextGameEnd[] = "GAME END";

		Style.Scale = 5; // Text size in scaling factor
		Style.PosX = 20; // Text X position
		Style.Colour =  0x3667; // Text RGB565 colour

		// Display GAME END on LT24
		RenderText(TextGameEnd, strlen(TextGameEnd), &Style, lt24);
	}

	char TextScore[] = "SCORE";

	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20; // Updates the Y position to next line
	Style.Scale = 8; // Text size
	Style.Colour = 0xFFE0; // Text colour

	// Displays SCORE on LT24
	RenderText(TextScore, strlen(TextScore), &Style, lt24);

	char NumScore[4]; // Store score value as string
	sprintf(NumScore, "%d", Score); // convert score number to string

	// Calculate score's x position to display text in middle
	uint8_t ScoreWidth = 0; // Stores total pixel width of the score number

	// Iterate through all the numbers in the score
	for(uint8_t i = 0; NumScore[i] != '\0'; i++) {

		// Calculate total width in pixels for displaying score number
		ScoreWidth += DiWidth[NumScore[i]-'0']*Style.Scale + Style.Scale;
	}

	ScoreWidth -= Style.Scale; // Remove trail space width
	Style.PosX = (LT24_WIDTH - ScoreWidth)/2; // Centres the text horizontally
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20; // Set the text below the previous text
	Style.Colour = 0xFD00; // Text colour

	// Displays the score value
	RenderText(NumScore, strlen(NumScore), &Style, lt24);

	char TextKeyPress[] = "PRESS KEY1 TO";
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20; // Set the text below the previous text
	Style.PosX = 24; // Text X position
	Style.Scale = 3; // Text size
	Style.Colour = 0x3667; // Text colour

	// Displays the instruction "PRESS KEY1 TO"
	RenderText(TextKeyPress, strlen(TextKeyPress), &Style, lt24);

	char TextKeyNum[] = "1";
	Style.PosX = 23 + 46*Style.Scale; // Set the text to overlap the previous text
	Style.Colour =  0xFFE0; // Text colour

	// Displays the number 1 with a different colour
	// over the 1 in the previous text.
	RenderText(TextKeyNum, strlen(TextKeyNum), &Style, lt24);

	char TextRestart[] = "RESTART";
	Style.PosY = Style.PosY + FONT_HEIGHT* Style.Scale + 20; // Set the text below the previous text
	Style.PosX = 30; // Text X position
	Style.Scale = 5; // Text size
	Style.Colour = 0x3667; // Text colour

	// Displays "RESTART" on LT24
	RenderText(TextRestart, strlen(TextRestart), &Style, lt24);

}
