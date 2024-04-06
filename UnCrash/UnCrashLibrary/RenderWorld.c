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
	Block->End = OB_SIDE-1;
	// Set the Y position of the world block on LCD
	Block->OffsetY = 0;
}

//
// Renders the world on the LCD by placing world blocks
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t lt24) {

	if(Block->Start >= OB_SIDE) {
		return;
	}

	// Local variables
	uint8_t ObsPlaceType= Block->ObsPlaceType;
	uint8_t ObsType1 = Block->ObsType1;
	uint8_t ObsType2 = Block->ObsType2;
	uint8_t ObsType3 = ObsType1 ^ ObsType2;
	uint8_t Start = Block->Start;
	uint8_t End = Block->End;
	uint16_t BlOffsetY = Block->OffsetY;

	uint8_t ObsX; 							// Left-X value for obstacles
	uint16_t StartPx = Start * OB_SIDE;		// block start pixel value to render from
	uint16_t BlHeight = End - Start + 1;	// block height in rows

	// Render left and right sidewalk
	static uint16_t SwOffsetY = 80;

	if(SwOffsetY) {
		LT24_copyFrameBuffer(lt24, &SidewalkLeft[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], 0, 0, SW_WIDTH, SwOffsetY);
		LT24_copyFrameBuffer(lt24, &SidewalkRight[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], LT24_WIDTH - SW_WIDTH, 0, SW_WIDTH, SwOffsetY);
	}
	LT24_copyFrameBuffer(lt24, SidewalkLeft, 0, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);
	LT24_copyFrameBuffer(lt24, SidewalkRight, LT24_WIDTH - SW_WIDTH, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);

	SwOffsetY++;
	if(SwOffsetY >= LT24_HEIGHT) {
		SwOffsetY = 0;
	}

	// first block : bit 0
	ObsX = SW_WIDTH;
	if(ObsPlaceType & 1u) {
		LT24_copyFrameBuffer(lt24, &Obstacles[ObsType1][StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	else {
		LT24_copyFrameBuffer(lt24, &Road[StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

	// middle block : bit 1
	ObsX += OB_SIDE;
	if((ObsPlaceType >> 1) & 1u) {
		LT24_copyFrameBuffer(lt24, &Obstacles[ObsType2][StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	else {
		LT24_copyFrameBuffer(lt24, &Road[StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

	// end block : bit 2
	ObsX += OB_SIDE;
	if((ObsPlaceType >> 2) & 1u) {
		LT24_copyFrameBuffer(lt24, &Obstacles[ObsType3][StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	else {
		LT24_copyFrameBuffer(lt24, &Road[StartPx], ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

}

//
// Shifts the block position related parameters by given shift value
//
void ShiftWorldBlock(WorldBlock WBlocks[], uint8_t ShiftY) {

	// check if the block after shifting is outside frame
	if(WBlocks[0].OffsetY + ShiftY >= LT24_HEIGHT) {

		// shift the data of the blocks
		for(uint8_t i = 0; i < 5; i++){
			WBlocks[i] = WBlocks[i+1];
		}

		// update the last block with new block design
		SetWorldBlock(&WBlocks[5]);
		WBlocks[5].Start = OB_SIDE;
		WBlocks[5].End = OB_SIDE;

	}

	// down shift first/bottom block
	WBlocks[0].OffsetY = WBlocks[0].OffsetY + ShiftY;
	WBlocks[0].Start = 0;
	WBlocks[0].End = WBlocks[0].End - ShiftY;

	// down shift the four middle blocks
	for(uint8_t i = 1; i < 5; i++) {
		WBlocks[i].OffsetY = WBlocks[i].OffsetY + ShiftY;
		WBlocks[i].Start = 0;
		WBlocks[i].End = OB_SIDE-1;
	}

	// down shift last/top world block
	WBlocks[5].OffsetY = 0;
	WBlocks[5].Start = WBlocks[5].Start - ShiftY;
	WBlocks[5].End = OB_SIDE-1;

}

//
// Renders the whole world on the LCD by placing world blocks
//
void RenderWorld(WorldBlock WBlocks[], PLT24Ctx_t lt24,  uint8_t ShiftY) {


	for(uint8_t i = 0; i < 6; i++)
	{
		RenderWorldBlock(&WBlocks[i], lt24);
	}

	ShiftWorldBlock(WBlocks, ShiftY);
}
