#include "RenderWorld.h"

//
// Generated 16 bit random number using Linear-Feedback Shift Register
//
uint16_t GetRandomNumber() {

	// seed for random number generation
	static uint16_t RandStart = 0xACE1u;

	uint16_t RandNum = RandStart;

	uint16_t feedback;

	/* taps: 16 15 feedback polynomial: x^16 + x^15 + 1 */
	feedback = ((RandNum >> 0) ^ (RandNum >> 1)) & 1u;
	RandNum = (RandNum >> 1) | (feedback << 7);

	RandStart = RandNum;

	return RandNum;
}

//
//	Creates game world blocks to be rendered
//
void SetWorldBlock(WorldBlock *Block) {

	uint16_t RandNum = GetRandomNumber();

	// Get the obstacle placement type : bits 0,1,2
	uint8_t ObsPlaceType = (RandNum & 7u);
	if(ObsPlaceType == 7u) {
		ObsPlaceType = 5u;
	}
	Block->ObsPlaceType = ObsPlaceType;

	// Get the coin placement type : bits 3,4,5
	Block->CoinPlaceType = ((RandNum >> 3) & 7u);
	// Get the first Obstacle type : bits 6,7,8
	Block->ObsType1 = ((RandNum >> 6) & 7u);
	// Get the second Obstacle type : bits 9,10,1
	Block->ObsType2 = ((RandNum >> 9) & 7u);
	// Set start and end rows to be rendered between;
	Block->Start = 0;
	Block->End = 63;
}

//
// Renders the world on the LCD by placing world blocks
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t lt24) {


	uint8_t ObsPlaceType= Block->ObsPlaceType;
	uint8_t ObsType1 = Block->ObsType1;
	uint8_t ObsType2 = Block->ObsType2;
	uint8_t ObsType3 = ObsType1 ^ ObsType2;
	uint8_t StartRow = Block->Start;
	uint8_t EndRow = Block->End;

	// Animate left and right sidewalk
	static uint16_t SidewalkOffsetY = 80;

	if(SidewalkOffsetY) {
		LT24_copyFrameBuffer(lt24, &SidewalkLeft[(320-SidewalkOffsetY)*24], 0, 0, 24, SidewalkOffsetY);
		LT24_copyFrameBuffer(lt24, &SidewalkRight[(320-SidewalkOffsetY)*24], 240 - 24, 0, 24, SidewalkOffsetY);
	}
	LT24_copyFrameBuffer(lt24, SidewalkLeft, 0, SidewalkOffsetY, 24, 320 - SidewalkOffsetY);
	LT24_copyFrameBuffer(lt24, SidewalkRight, 240 - 24, SidewalkOffsetY, 24, 320 - SidewalkOffsetY);

	SidewalkOffsetY = (SidewalkOffsetY + 1);
	if(SidewalkOffsetY >= 320) {
		SidewalkOffsetY = 0;
	}



}
