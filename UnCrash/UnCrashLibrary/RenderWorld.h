#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"



//
// Generates random number using Linear-Feedback Shift Register
// - returns 16 bit random number
//
uint16_t GetRandomNumber();

//
//	Creates game world blocks to be rendered
//	- no returns as the value is directly written to address
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

#endif /* RENDERWORLD_H_ */
