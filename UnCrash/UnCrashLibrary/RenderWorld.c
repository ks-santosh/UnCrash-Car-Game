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

	static uint8_t PrvObsPlaceType = 0;

	uint16_t RandNum = GetRandomNumber();

	// Get the obstacle placement type : bits 0,1,2
	uint8_t ObsPlaceType = (RandNum & 7u);

	// to make way for the car
	if(PrvObsPlaceType) {
		ObsPlaceType = 0;
	}
	// obstacles should not occupy all the boxes
	else if(ObsPlaceType == 7u) {
		ObsPlaceType = 5u;
	}


	PrvObsPlaceType = ObsPlaceType;

	Block->ObsPlaceType = ObsPlaceType;

	// Get the coin placement type : bits 3,4,5
	uint8_t CoinPlaceType = ((RandNum >> 3) & 7u);

	// Coins and obstacles should not overlap
	CoinPlaceType = (~ObsPlaceType) & (CoinPlaceType);

	Block->CoinPlaceType = CoinPlaceType;

	// Get the first Obstacle type : bits 6,7,8
	Block->ObsType[0] = ((RandNum >> 6) & 7u);
	// Get the second Obstacle type : bits 9,10,11
	Block->ObsType[1] = ((RandNum >> 9) & 7u);
	// Get the third Obstacle type : bits 12, 13, 14
	Block->ObsType[2] = ((RandNum >> 12) & 7u);
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
	uint8_t CoinPlaceType = Block->CoinPlaceType;
	uint8_t *ObsType = Block->ObsType;
	uint8_t Start = Block->Start;
	uint8_t End = Block->End;
	uint16_t BlOffsetY = Block->OffsetY;

	uint8_t ObsX; 							// Left-X value for obstacles
	uint16_t StartPx = Start * OB_SIDE;		// block start pixel value to render from
	uint16_t BlHeight = End - Start + 1;	// block height in rows

	// first block : bit 0
	ObsX = SW_WIDTH;
	const unsigned short *SetBlock;
	if(ObsPlaceType & 1u) {
		SetBlock = &Obstacles[*ObsType][StartPx];
	}
	else if (CoinPlaceType & 1u){
		SetBlock = &Coin[StartPx];
	}
	else {
		SetBlock = &Road[StartPx];
	}
	LT24_copyFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);

	// middle block : bit 1
	ObsX += OB_SIDE;
	if((ObsPlaceType >> 1) & 1u) {
		SetBlock = &Obstacles[*ObsType++][StartPx];
	}
	else if ((CoinPlaceType >> 1) & 1u){
		SetBlock = &Coin[StartPx];
	}
	else {
		SetBlock = &Road[StartPx];
	}
	LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);

	// end block : bit 2
	ObsX += OB_SIDE;
	if((ObsPlaceType >> 2) & 1u) {
		SetBlock = &Obstacles[*ObsType++][StartPx];
	}
	else if ((CoinPlaceType >> 2) & 1u){
		SetBlock = &Coin[StartPx];
	}
	else {
		SetBlock = &Road[StartPx];
	}
	LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
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

	// Render left and right sidewalk
	static uint16_t SwOffsetY = 0;

	if(SwOffsetY) {
		LT24_copyFrameBuffer(lt24, &SidewalkLeft[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], 0, 0, SW_WIDTH, SwOffsetY);
		LT24_copyFrameBuffer(lt24, &SidewalkRight[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], LT24_WIDTH - SW_WIDTH, 0, SW_WIDTH, SwOffsetY);
	}
	LT24_copyFrameBuffer(lt24, SidewalkLeft, 0, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);
	LT24_copyFrameBuffer(lt24, SidewalkRight, LT24_WIDTH - SW_WIDTH, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);

	SwOffsetY += ShiftY;
	if(SwOffsetY >= LT24_HEIGHT) {
		SwOffsetY = 0;
	}

	// Render obstacles and road
	for(uint8_t i = 0; i < 6; i++)
	{
		RenderWorldBlock(&WBlocks[i], lt24);
	}

	// down shift the world
	ShiftWorldBlock(WBlocks, ShiftY);
}

//
// Sets the initial game world configuration
//
void InitWorldBlock(WorldBlock WBlocks[]) {
	// Block 0
	WBlocks[0].ObsPlaceType = 5;
	WBlocks[0].ObsType[0] = 0;
	WBlocks[0].ObsType[1] = 1;
	WBlocks[0].ObsType[2] = 2;
	WBlocks[0].CoinPlaceType = 2;
	WBlocks[0].Start = 0;
	WBlocks[0].End = OB_SIDE - 1;
	WBlocks[0].OffsetY = 4*OB_SIDE;

	// Block 1
	WBlocks[1].ObsPlaceType = 5;
	WBlocks[1].ObsType[0] = 3;
	WBlocks[1].ObsType[1] = 4;
	WBlocks[1].ObsType[2] = 5;
	WBlocks[1].CoinPlaceType = 2;
	WBlocks[1].Start = 0;
	WBlocks[1].End = OB_SIDE - 1;
	WBlocks[1].OffsetY = 3*OB_SIDE;

	// Block 2
	WBlocks[2].ObsPlaceType = 5;
	WBlocks[2].ObsType[0] = 6;
	WBlocks[2].ObsType[1] = 7;
	WBlocks[2].ObsType[2] = 0;
	WBlocks[2].CoinPlaceType = 2;
	WBlocks[2].Start = 0;
	WBlocks[2].End = OB_SIDE - 1;
	WBlocks[2].OffsetY = 2*OB_SIDE;

	// Block 3
	WBlocks[3].ObsPlaceType = 5;
	WBlocks[3].ObsType[0] = 1;
	WBlocks[3].ObsType[1] = 2;
	WBlocks[3].ObsType[2] = 3;
	WBlocks[3].CoinPlaceType = 2;
	WBlocks[3].Start = 0;
	WBlocks[3].End = OB_SIDE - 1;
	WBlocks[3].OffsetY = OB_SIDE;

	// Block 4
	WBlocks[4].ObsPlaceType = 5;
	WBlocks[4].ObsType[0] = 4;
	WBlocks[4].ObsType[1] = 5;
	WBlocks[4].ObsType[2] = 6;
	WBlocks[4].CoinPlaceType = 2;
	WBlocks[4].Start = 0;
	WBlocks[4].End = OB_SIDE -1;
	WBlocks[4].OffsetY = 0;

	// Block 5
	WBlocks[5].ObsPlaceType = 5;
	WBlocks[5].ObsType[0] = 7;
	WBlocks[5].ObsType[1] = 0;
	WBlocks[5].ObsType[2] = 1;
	WBlocks[5].CoinPlaceType = 2;
	WBlocks[5].Start = OB_SIDE;
	WBlocks[5].End = OB_SIDE;
	WBlocks[5].OffsetY = 0;

}

//
// Displays the grayscale version of the frame
//
void RenderGrayScreen(WorldBlock WBlocks[], PLT24Ctx_t lt24) {

	WorldBlock Block;
	for(uint8_t i = 0; i < 6; i++)
	{
		Block = WBlocks[i];

		// Local variables
		uint8_t ObsPlaceType= Block.ObsPlaceType;
		uint8_t CoinPlaceType = Block.CoinPlaceType;
		uint8_t *ObsType = Block.ObsType;
		uint8_t Start = Block.Start;
		uint8_t End = Block.End;
		uint16_t BlOffsetY = Block.OffsetY;

		uint8_t ObsX; 							// Left-X value for obstacles
		uint16_t StartPx = Start * OB_SIDE;		// block start pixel value to render from
		uint16_t BlHeight = End - Start + 1;	// block height in rows

		// first block : bit 0
		ObsX = SW_WIDTH;
		const unsigned short *SetBlock;
		if(ObsPlaceType & 1u) {
			SetBlock = &Obstacles[*ObsType][StartPx];
		}
		else if (CoinPlaceType & 1u){
			SetBlock = &Coin[StartPx];
		}
		else {
			SetBlock = &Road[StartPx];
		}
		LT24_copyGrayFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);

		// middle block : bit 1
		ObsX += OB_SIDE;
		if((ObsPlaceType >> 1) & 1u) {
			SetBlock = &Obstacles[*ObsType++][StartPx];
		}
		else if ((CoinPlaceType >> 1) & 1u){
			SetBlock = &Coin[StartPx];
		}
		else {
			SetBlock = &Road[StartPx];
		}
		LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);

		// end block : bit 2
		ObsX += OB_SIDE;
		if((ObsPlaceType >> 2) & 1u) {
			SetBlock = &Obstacles[*ObsType++][StartPx];
		}
		else if ((CoinPlaceType >> 2) & 1u){
			SetBlock = &Coin[StartPx];
		}
		else {
			SetBlock = &Road[StartPx];
		}
		LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

	LT24_copyGrayFrameBuffer(lt24, SidewalkLeft, 0, 0, SW_WIDTH, LT24_HEIGHT);
	LT24_copyGrayFrameBuffer(lt24, SidewalkRight, LT24_WIDTH - SW_WIDTH, 0, SW_WIDTH, LT24_HEIGHT);


}
