#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"

//
// Copy frame buffer to display after converting it to grayscale image
// - returns 0 if successful
//
HpsErr_t LT24_copyGrayFrameBuffer( PLT24Ctx_t ctx, const unsigned short* framebuffer, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height );

//
// Function to set single colour to a part of the display
// - returns true if successful
//
HpsErr_t LT24_drawColourWindow( PLT24Ctx_t ctx, unsigned short Colour, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height );

//
// Generates random number using Linear-Feedback Shift Register
// - returns 16 bit random number
//
uint16_t GetRandomNumber();

//
//	Creates game world blocks to be rendered
//	- no returns as the value is directly written to address
//
void SetWorldBlock(WorldBlock *Block);

//
// Renders the world block piece on the LCD
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t ctx);

//
// Shifts the block position related parameters by given shift value
//
void ShiftWorldBlock(WorldBlock WBlocks[], uint8_t ShiftY);

//
// Renders the whole world on the LCD by placing world blocks
//
void RenderWorld(WorldBlock *Block, PLT24Ctx_t ctx, uint8_t ShiftY);

//
// Sets the initial game world configuration
//
void InitWorldBlock(WorldBlock WBlocks[]);

//
// Displays the grayscale version of the frame
//
void RenderGrayScreen(WorldBlock WBlocks[], PLT24Ctx_t lt24);

#endif /* RENDERWORLD_H_ */
