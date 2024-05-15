/*
 * File: CheckCollision.c
 *
 * Details : Detects collisions between the player's car
 * and other objects within the game world.
 *
 * Author: Santosh K S
 *
 */

// Header inclusion
#include "CheckCollision.h"

//
// Function: SetCollisionAction
// Details: Determines the pixel value of the game world at the specified coordinates,
// updating the crash status or score based on its value.
// Arguments: World blocks, x-y coordinates, collision status
// Return: Void. Updates the collision status value passed in argument.
//
void SetCollisionAction(WorldBlock WBlocks[], uint16_t Px, uint16_t Py, CollisionEvent *CollSts) {

	// Pixel colour
	uint16_t Pixel = 0x32D0; // Colour of road

	// Shifting the X-origin after sidewalk
	Px = Px - SW_WIDTH; // Subtract sidewalk width

	// Find which of the three box of the WorldBlocks the point falls in
	uint8_t Box = Px >> 6;	// Px divided by (2^6) 64 which is the box width

	// Shifting origin of X relative to the box
	Px = Px - Box*OB_SIDE;

	// Index of obstacle type ObsType
	uint8_t ObsId = Box;

	// Bits in box represent the position
	Box = (1 << Box);

	// Flag to check if car collided with obstacle or coin
	bool CollType = false; // True: Obstacle False: Coin

	// To track the block id where point lies
	bool WBlockColl = false; // false - collision happened in WBlocks[1]

	// Check in WBlock1 - second block from bottom
	// if Y point falls inside it
	if(Py >= WBlocks[1].OffsetY) {

		// Shift origin of Y to WBlock1
		Py = Py - WBlocks[1].OffsetY;

		// If box has obstacles
		if(Box & WBlocks[1].ObsPlaceType) {

			// Get the pixel value at the coordinate
			Pixel = Obstacles[WBlocks[1].ObsType[ObsId]][Py*64 + Px];
			CollType = true; // True: Obstacle False: Coin
		}

		// If box has coins
		else if(Box & WBlocks[1].CoinPlaceType) {

			// Get the pixel value at the coordinate
			Pixel = Coin[Py*64 + Px];
		}
	}

	// Check in WBlock2 - third block from bottom otherwise
	else {

		WBlockColl = true;  // true - collision happened in WBlocks[2]

		// Shift origin of Y to WBlock2
		Py = Py - WBlocks[2].OffsetY;

		// If box has obstacles
		if(Box & WBlocks[2].ObsPlaceType) {

			// Get the pixel value at the coordinate
			Pixel = Obstacles[WBlocks[2].ObsType[ObsId]][Py*64 + Px];

			CollType = true; // True: Obstacle False: Coin
		}
		// If box has coins
		else if(Box & WBlocks[2].CoinPlaceType) {
			// Get the pixel value at the coordinate
			Pixel = Coin[Py*64 + Px];
		}
	}

	// The point doesn't fall on road if
	// the pixel value doesn't match the road's colour
	if(Pixel != ROAD_COLOUR) {

		// If collision with obstacle
		// True: Obstacle False: Coin
		if(CollType) {
			CollSts->Crash = true; // Set crash status
		}

		// If collision with coin
		else {

			CollSts->Crash = false; // reset crash status

			CollSts->Score++; // Increment score

			// Remove the coin from the block
			// if collision happened in block2
			if(WBlockColl) {
				// Remove coin from WBlocks[2]
				WBlocks[2].CoinPlaceType = (~Box) & WBlocks[2].CoinPlaceType;
			}
			else {
				// Remove coin from WBlocks[1]
				WBlocks[1].CoinPlaceType = (~Box) & WBlocks[1].CoinPlaceType;
			}
		}
	}

}

//
// Function: CheckCollision
// Details: Verifies if each corner of the car collides with obstacles
// or coins, updating the score in case of a coin collision and setting
// the crash status upon collision with obstacles.
// Arguments: World blocks, car position and collision status
// Return: Void. Updates the collision status value passed in argument.
//
void CheckCollision(WorldBlock WBlocks[], uint16_t CarPosX, CollisionEvent *CollSts) {

	static uint16_t PrvScore = 0; // Previous score

	// Check car's top-left corner
	SetCollisionAction(WBlocks, CarPosX+2, CAR_POS_Y+2, CollSts);
	// If crash or change in score
	if((CollSts->Crash) || (PrvScore != CollSts->Score)) {
		// Update previous score
		PrvScore = CollSts->Score;
		return;
	}

	// Check car's bottom-right corner
	SetCollisionAction(WBlocks, CarPosX + CAR_WIDTH - 3, CAR_POS_Y + CAR_HEIGHT - 3,CollSts);
	// If crash or change in score
	if((CollSts->Crash) || (PrvScore != CollSts->Score)) {
		// Update previous score
		PrvScore = CollSts->Score;
		return;
	}

	// Check car's top-right corner
	SetCollisionAction(WBlocks, CarPosX + CAR_WIDTH - 3, CAR_POS_Y + 2,CollSts);
	// If crash or change in score
	if((CollSts->Crash) || (PrvScore != CollSts->Score)) {
		// Update previous score
		PrvScore = CollSts->Score;
		return;
	}

	// Check car's bottom-left corner
	SetCollisionAction(WBlocks, CarPosX + 2, CAR_POS_Y + CAR_HEIGHT - 3,CollSts);
	// If crash or change in score
	if((CollSts->Crash) || (PrvScore != CollSts->Score)) {
		// Update previous score
		PrvScore = CollSts->Score;
		return;
	}

}
