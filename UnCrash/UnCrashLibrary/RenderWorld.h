#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"

// Sidewalk Dimensions
#define SW_WIDTH 24u
#define SW_HEIGHT 320u

// Obstacle Dimensions
#define OB_SIDE 64u

//
// Sets the design and placement of game world's basic blocks
//
typedef struct WorldBlock {
	uint8_t ObsPlaceType;	// Obstacle placement type
	uint8_t CoinPlaceType;	// Coin placement type
	uint8_t ObsType1;		// select obstacle 1
	uint8_t ObsType2;		// select obstacle 2
	uint8_t Start;			// starting row to render from
	uint8_t End;			// end row to render till
	uint16_t OffsetY;		// The y-axis point on LCD to draw from
} WorldBlock;

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
