#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"

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
// Renders the world on the LCD by placing world blocks
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t ctx);

#endif /* RENDERWORLD_H_ */
