/*
 * File: RenderWorld.c
 *
 * Details : Defines and renders the game world layout, comprising
 * obstacles, coins, roads, and sidewalks. It set, configures, shifts
 * and displays the game world on LT24.
 *
 * Author: Santosh K S
 *
 */

// Header inclusion
#include "RenderWorld.h"

//
// Function: LT24_copyGrayFrameBuffer
// Details: Copy frame buffer to display after converting it to grayscale image.
// Arguments: Driver context, frame buffer address, starting position, frame dimensions
// Return: 0 if successful
//
HpsErr_t LT24_copyGrayFrameBuffer( PLT24Ctx_t ctx, const unsigned short* framebuffer, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height ) {

	//Define Window (setWindow validates context for us)
    HpsErr_t status = LT24_setWindow(ctx, xleft, ytop, width, height);

    // Check if window validation was successful
    if (IS_ERROR(status)) return status;

    //And copy the required number of pixels
    unsigned int cnt = (height * width);

    // Variables to store RGB and pixel values
    unsigned short Px, red, green, blue, grayscale;

    // Iterate through all pixels of frame buffer
    while (cnt--) {

    	Px = *framebuffer++; // Get colour value

		// Split colour value into RGB components
		red = ((Px & 0xF800)>>11); //
		green = ((Px & 0x07E0)>>5);
		blue = (Px & 0x001F);

		// Convert RGB565 to gray colour using luminance method
		// The coefficients of the RGB represent intensity of each color in gray
		// Source code from: https://stackoverflow.com/questions/58449462/rgb565-to-grayscale

		grayscale = (0.2126 * red) + (0.7152 * green / 2.0) + (0.0722 * blue);

		// Join the components back into 565
		Px = (grayscale << 11) + (grayscale << 6) + grayscale;

		// Write the pixel to display
		LT24_write(ctx, true, Px);
    }

    return ERR_SUCCESS; // Return status success
}

//
// Function: LT24_drawColourWindow
// Details: Function colour a part of the display with
// with single colour value.
// Arguments: Driver context, RGB565 colour value, starting position, frame dimensions
// Return: true if successful
//
HpsErr_t LT24_drawColourWindow( PLT24Ctx_t ctx, unsigned short Colour, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height ) {

	// Define Window (setWindow validates context for us)
    HpsErr_t status = LT24_setWindow(ctx, xleft, ytop, width, height);

    // Check if window validation was successful
    if (IS_ERROR(status)) return status;

    // Get the number of pixels to be coloured on display
    unsigned int cnt = (height * width);

    // Iterate through all the pixels in the frame
    while (cnt--) {

    	// Write the pixel colour to display
        LT24_write(ctx, true, Colour);
    }

    return ERR_SUCCESS; // Return status success
}

//
// Function: GetRandomNumber
// Details: Generates 16 bit random number using Linear-Feedback Shift Register
// Arguments: Void.
// Return: 16 bit unsigned random number
//
uint16_t GetRandomNumber() {

	// Seed for random number generation.
	// Every function call will change the seed.
	static uint16_t RandStart = 0xACE1u;

	uint16_t RandNum = RandStart; // Random number

	uint16_t feedback;

	// taps: 16 15 feedback polynomial: x^16 + x^15 + 1
	// Source code from: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
	feedback = ((RandNum >> 0) ^ (RandNum >> 1)) & 1u;

	// Get random number
	RandNum = (RandNum >> 1) | (feedback << 7);

	// Update the starting random number
	RandStart = RandNum;

	return RandNum; // Return random number
}

//
// Function: SetWorldBlock
// Details: Creates game world blocks to be rendered
// from the random number.
// Arguments: Worldblock structure
// Return: Void. Configures the world block sent in the argument.
//
void SetWorldBlock(WorldBlock *Block) {

	// To keep track of previous obstacle type
	static uint8_t PrvObsPlaceType = 0;

	// Get random number
	uint16_t RandNum = GetRandomNumber();

	// Get the obstacle placement type : bits 0,1,2
	uint8_t ObsPlaceType = (RandNum & 7u);

	// If the previous world block contains obstacle the
	// next worlblock should be just road without obstacles.
	if(PrvObsPlaceType) {

		ObsPlaceType = 0; // No obstacles
	}
	// Obstacles should not occupy all the three boxes
	else if(ObsPlaceType == 7u) {

		ObsPlaceType = 5u; // Fill obstacle only in the boxes at ends
	}

	// Update the previous obstacle types
	PrvObsPlaceType = ObsPlaceType;

	// Store the obstacle type in the structure
	Block->ObsPlaceType = ObsPlaceType;

	// Get the coin placement type : bits 3,4,5
	uint8_t CoinPlaceType = ((RandNum >> 3) & 7u);

	// Don't place coins at the boxes with obstacles
	CoinPlaceType = (~ObsPlaceType) & (CoinPlaceType);

	// Store the coin positions in the structure
	Block->CoinPlaceType = CoinPlaceType;

	// Get the first Obstacle type : bits 6,7,8
	Block->ObsType[0] = ((RandNum >> 6) & 7u);
	// Get the second Obstacle type : bits 9,10,11
	Block->ObsType[1] = ((RandNum >> 9) & 7u);
	// Get the third Obstacle type : bits 12, 13, 14
	Block->ObsType[2] = ((RandNum >> 12) & 7u);

	// Set start and end rows to display part of world block
	Block->Start = 0; // The top row from where the block should be displayed
	Block->End = OB_SIDE-1; // The bottom row till where the block should be displayed

	// Set the Y position of the world block on LCD
	Block->OffsetY = 0;
}

//
// Function: RenderWorldBlock
// Details: Renders the game world blocks on LT24 display
// Arguments: world block address, LT24 driver context
// Return: Void.
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t lt24) {

	// If the starting row to display exceeds the size
	// of box, then return as there is nothing to display.
	if(Block->Start >= OB_SIDE) {
		return;
	}

	// Local variables
	uint8_t ObsPlaceType= Block->ObsPlaceType; // Obstacle placement position
	uint8_t CoinPlaceType = Block->CoinPlaceType; // Coin placement position
	uint8_t *ObsType = Block->ObsType; // Obstacle type to be places at each position
	uint8_t Start = Block->Start; // The top row from where the block should be displayed
	uint8_t End = Block->End; // The bottom row till where the block should be displayed
	uint16_t BlOffsetY = Block->OffsetY; // The top-Y of display at which the block should be displayed

	uint8_t ObsX; // Left-X value for obstacles
	uint16_t StartPx = Start * OB_SIDE; // Block start pixel index value to render from
	uint16_t BlHeight = End - Start + 1; // Block height from the start to end displayed

	// First block : bit 0
	ObsX = SW_WIDTH; // Display block starting from the sidewalk width

	// Pointer to blocks of worldblock
	const unsigned short *SetBlock;

	// If obstacle at bit 0 (first or leftmost block)
	if(ObsPlaceType & 1u) {

		// Set the pointer to the obstacle type
		SetBlock = &Obstacles[*ObsType][StartPx];

		// Display the world block from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else if coin at bit 0 (first or leftmost block)
	else if (CoinPlaceType & 1u){

		// Set the pointer to the coin image pixel array
		SetBlock = &Coin[StartPx];

		// Display the world block with coin from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else just draw empty road
	else {

		// Display road which is simply a mono-colour box
		LT24_drawColourWindow(lt24, ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

	// Middle block : bit 1
	ObsX += OB_SIDE; // Shift the position for second block

	// If obstacle at bit 1 (middle block)
	if((ObsPlaceType >> 1) & 1u) {

		// Set the pointer to the obstacle type
		SetBlock = &Obstacles[*ObsType++][StartPx];

		// Display the world block from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else if coin at bit 1 (middle block)
	else if ((CoinPlaceType >> 1) & 1u){

		// Set the pointer to the coin image pixel array
		SetBlock = &Coin[StartPx];

		// Display the world block with coin from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else just draw empty road
	else {

		// Display road which is simply a mono-colour box
		LT24_drawColourWindow(lt24, ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}


	// End block : bit 2
	ObsX += OB_SIDE; // Shift the position for third block

	// If obstacle at bit 2 (end or leftmost block)
	if((ObsPlaceType >> 2) & 1u) {

		// Set the pointer to the obstacle type
		SetBlock = &Obstacles[*ObsType++][StartPx];

		// Display the world block from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else if coin at bit 2 (end or leftmost block)
	else if ((CoinPlaceType >> 2) & 1u){

		// Set the pointer to the coin image pixel array
		SetBlock = &Coin[StartPx];

		// Display the world block with coin from Y offset
		// Display the block from the start to end rows
		LT24_copyFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}
	// Else just draw empty road
	else {

		// Display road which is simply a mono-colour box
		LT24_drawColourWindow(lt24,ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
	}

}

//
// Function: ShiftWorldBlock
// Details: Shifts the block position related parameters by
// given shift value vertically. This gives a perception that
// car is moving forward when infact the game world is moving back.
// Arguments: Worldblock array, vertical shift value
// Return: Void. Updates the world block positional parameters in the WBlock argument.
//
void ShiftWorldBlock(WorldBlock WBlocks[], uint8_t ShiftY) {

	// Check if the 0th block after shifting down is completely outside frame
	if(WBlocks[0].OffsetY + ShiftY >= LT24_HEIGHT) {

		// Rearrange the blocks in the block array
		// As block 0 is completely out of view,
		// shift the block 1 to block 0 and so on with other blocks.
		for(uint8_t i = 0; i < 5; i++){
			WBlocks[i] = WBlocks[i+1];
		}

		// Update the last block with new block design as
		// the top block (block5) position is now empty
		SetWorldBlock(&WBlocks[5]);

		// Set block 5 start and end rows between which the frame will be displayed
		// As block 5 is not in the view, set the start and end to block size
		WBlocks[5].Start = OB_SIDE;
 		WBlocks[5].End = OB_SIDE;
	}

	// Down shift bottom block (block 0)
	WBlocks[0].OffsetY = WBlocks[0].OffsetY + ShiftY;
	WBlocks[0].Start = 0; // Set the start row to 0

	// Show till the cropped end row as shifting down will move the shifted part out of display
	WBlocks[0].End = WBlocks[0].End - ShiftY;

	// Down shift the four middle blocks
	for(uint8_t i = 1; i < 5; i++) {

		// Shift the position of blocks down
		WBlocks[i].OffsetY = WBlocks[i].OffsetY + ShiftY;

		// As the blocks are in complete view so the block images
		// will be displayed completely from start to end row.
		WBlocks[i].Start = 0; // Set the start row to -
		WBlocks[i].End = OB_SIDE-1; // Set end row to block size
	}

	// Down shift last world block (also the top block on LT24)
	WBlocks[5].OffsetY = 0; // Set the top-Y position of block
	WBlocks[5].Start = WBlocks[5].Start - ShiftY; // Shift the starting point of the block

	// The block is shifting from top so the end will be in view
	WBlocks[5].End = OB_SIDE-1; // Set the end row to block size

}

//
// Function: RenderWorld
// Details: Renders the world consisting of six world blocks on the LT24 display.
// Arguments: World block array, LT24 driver context, vertical shift value
// Return: Void.
//
void RenderWorld(WorldBlock WBlocks[], PLT24Ctx_t lt24,  uint8_t ShiftY) {

	// To keep track of last shifted value for sidewalk
	static uint16_t SwOffsetY = 0;

	// If there is an offset
	if(SwOffsetY) {

		// After the sidewalk is shifted down, this will take the sidewalk shifted out of display
		// and put it at the top empty spot. This will give an impression that the sidewalk is
		// continuously moving back.

		// Put shifted left sidewalk at top
		LT24_copyFrameBuffer(lt24, &SidewalkLeft[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], 0, 0, SW_WIDTH, SwOffsetY);

		// Put shifted right sidewalk at top
		LT24_copyFrameBuffer(lt24, &SidewalkRight[(LT24_HEIGHT-SwOffsetY)*SW_WIDTH], LT24_WIDTH - SW_WIDTH, 0, SW_WIDTH, SwOffsetY);
	}

	// Shift the left sidewalk vertically down
	LT24_copyFrameBuffer(lt24, SidewalkLeft, 0, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);

	// Shift the right sidewalk vertically down
	LT24_copyFrameBuffer(lt24, SidewalkRight, LT24_WIDTH - SW_WIDTH, SwOffsetY, SW_WIDTH, LT24_HEIGHT - SwOffsetY);

	// Increment the shifted value
	SwOffsetY += ShiftY;

	// If shifted value is more then the display height
	if(SwOffsetY >= LT24_HEIGHT) {
		SwOffsetY = 0; // Reset the shift value
	}

	// Renders all the world blocks on the LT24 display
	for(uint8_t i = 0; i < 6; i++)
	{
		RenderWorldBlock(&WBlocks[i], lt24);
	}

	// Down shift the world after display
	ShiftWorldBlock(WBlocks, ShiftY);
}

//
// Function: InitWorldBlock
// Details: Sets the initial game world configuration. The game
// will always start with this configuration of blocks, obstacles and coins.
// Arguments: World block array.
// Return: Void.
//
void InitWorldBlock(WorldBlock WBlocks[]) {
	// Block 0
	WBlocks[0].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[0].ObsType[0] = 0; // Set the leftmost obstacle type
	WBlocks[0].ObsType[1] = 1; // Set middle obstacle type
	WBlocks[0].ObsType[2] = 2; // Set the rightmost obstacle type
	WBlocks[0].CoinPlaceType = 0; // No coins placed at start
	WBlocks[0].Start = 0; // Set the block start row for display
	WBlocks[0].End = OB_SIDE - 1; // Set the block end row for display
	WBlocks[0].OffsetY = 4*OB_SIDE; // Set the top-Y position of the block

	// Block 1
	WBlocks[1].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[1].ObsType[0] = 3; // Set the leftmost obstacle type
	WBlocks[1].ObsType[1] = 4; // Set middle obstacle type
	WBlocks[1].ObsType[2] = 5; // Set the rightmost obstacle type
	WBlocks[1].CoinPlaceType = 0; // No coins placed at start
	WBlocks[1].Start = 0; // Set the block start row for display
	WBlocks[1].End = OB_SIDE - 1; // Set the block end row for display
	WBlocks[1].OffsetY = 3*OB_SIDE; // Set the top-Y position of the block

	// Block 2
	WBlocks[2].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[2].ObsType[0] = 6; // Set the leftmost obstacle type
	WBlocks[2].ObsType[1] = 7; // Set middle obstacle type
	WBlocks[2].ObsType[2] = 0; // Set the rightmost obstacle type
	WBlocks[2].CoinPlaceType = 0; // No coins placed at start
	WBlocks[2].Start = 0; // Set the block start row for display
	WBlocks[2].End = OB_SIDE - 1; // Set the block end row for display
	WBlocks[2].OffsetY = 2*OB_SIDE; // Set the top-Y position of the block

	// Block 3
	WBlocks[3].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[3].ObsType[0] = 1; // Set the leftmost obstacle type
	WBlocks[3].ObsType[1] = 2; // Set middle obstacle type
	WBlocks[3].ObsType[2] = 3; // Set the rightmost obstacle type
	WBlocks[3].CoinPlaceType = 2; // No coins placed at start
	WBlocks[3].Start = 0; // Set the block start row for display
	WBlocks[3].End = OB_SIDE - 1; // Set the block end row for display
	WBlocks[3].OffsetY = OB_SIDE; // Set the top-Y position of the block

	// Block 4
	WBlocks[4].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[4].ObsType[0] = 4; // Set the leftmost obstacle type
	WBlocks[4].ObsType[1] = 5; // Set middle obstacle type
	WBlocks[4].ObsType[2] = 6; // Set the rightmost obstacle type
	WBlocks[4].CoinPlaceType = 2; // No coins placed at start
	WBlocks[4].Start = 0; // Set the block start row for display
	WBlocks[4].End = OB_SIDE -1; // Set the block end row for display
	WBlocks[4].OffsetY = 0; // Set the top-Y position of the block

	// Block 5
	WBlocks[5].ObsPlaceType = 5; // Place obstacle at both ends
	WBlocks[5].ObsType[0] = 7; // Set the leftmost obstacle type
	WBlocks[5].ObsType[1] = 0; // Set middle obstacle type
	WBlocks[5].ObsType[2] = 1; // Set the rightmost obstacle type
	WBlocks[5].CoinPlaceType = 2; // No coins placed at start
	WBlocks[5].Start = OB_SIDE; // Set the block start row for display
	WBlocks[5].End = OB_SIDE; // Set the block end row for display
	WBlocks[5].OffsetY = 0; // Set the top-Y position of the block

}

//
// Function: RenderGrayScreen
// Details: Displays the world blocks in grayscale colour format.
// Arguments: World block array, Lt24 display driver context
// Return: Void.
//
void RenderGrayScreen(WorldBlock WBlocks[], PLT24Ctx_t lt24) {

	WorldBlock Block;

	// Display through all the 6 blocks
	for(uint8_t i = 0; i < 6; i++)
	{
		Block = WBlocks[i];

		// Local variables
		uint8_t ObsPlaceType= Block.ObsPlaceType; // Obstacle placement position
		uint8_t CoinPlaceType = Block.CoinPlaceType; // Coin placement position
		uint8_t *ObsType = Block.ObsType; // Obstacle type to be places at each position
		uint8_t Start = Block.Start; // The top row from where the block should be displayed
		uint8_t End = Block.End; // The bottom row till where the block should be displayed
		uint16_t BlOffsetY = Block.OffsetY; // The top-Y of display at which the block should be displayed

		uint8_t ObsX; // Left-X value for obstacles
		uint16_t StartPx = Start * OB_SIDE; // block start pixel value to render from
		uint16_t BlHeight = End - Start + 1; // block height in rows

		// First block : bit 0
		ObsX = SW_WIDTH; // Display block starting from the sidewalk width

		// Pointer to blocks of worldblock
		const unsigned short *SetBlock;

		// If obstacle at bit 0 (first or leftmost block)
		if(ObsPlaceType & 1u) {

			// Set the pointer to the obstacle type
			SetBlock = &Obstacles[*ObsType][StartPx];

			// Display the world block from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else if coin at bit 0 (first or leftmost block)
		else if (CoinPlaceType & 1u){

			// Set the pointer to the coin image pixel array
			SetBlock = &Coin[StartPx];

			// Display the world block with coin from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24, SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else just draw empty road
		else {
			// Display grayscale road which is simply a mono-colour box
			LT24_drawColourWindow(lt24, ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}

		// Middle block : bit 1
		ObsX += OB_SIDE; // Shift the position for second block

		// If obstacle at bit 1 (middle block)
		if((ObsPlaceType >> 1) & 1u) {

			// Set the pointer to the obstacle type
			SetBlock = &Obstacles[*ObsType++][StartPx];

			// Display the world block from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else if coin at bit 1 (middle block)
		else if ((CoinPlaceType >> 1) & 1u){

			// Set the pointer to the coin image pixel array
			SetBlock = &Coin[StartPx];

			// Display the world block with coin from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else just draw empty road
		else {

			// Display grayscale road which is simply a mono-colour box
			LT24_drawColourWindow(lt24,ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}

		// End block : bit 2
		ObsX += OB_SIDE; // Shift the position for third block

		// If obstacle at bit 2 (end or leftmost block)
		if((ObsPlaceType >> 2) & 1u) {

			// Set the pointer to the obstacle type
			SetBlock = &Obstacles[*ObsType++][StartPx];

			// Display the world block from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else if coin at bit 2 (end or leftmost block)
		else if ((CoinPlaceType >> 2) & 1u){

			// Set the pointer to the coin image pixel array
			SetBlock = &Coin[StartPx];

			// Display the world block with coin from Y offset
			// Display the block from the start to end rows in grayscale colour
			LT24_copyGrayFrameBuffer(lt24,SetBlock, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}
		// Else just draw empty road
		else {

			// Display grayscale road which is simply a mono-colour box
			LT24_drawColourWindow(lt24,ROAD_COLOUR, ObsX, BlOffsetY, OB_SIDE, BlHeight);
		}

	}

	// Display the left and right sidewalk in grayscale colour
	LT24_copyGrayFrameBuffer(lt24, SidewalkLeft, 0, 0, SW_WIDTH, LT24_HEIGHT);
	LT24_copyGrayFrameBuffer(lt24, SidewalkRight, LT24_WIDTH - SW_WIDTH, 0, SW_WIDTH, LT24_HEIGHT);

}
