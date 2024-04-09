/*
 * File: CheckCollision.c
 *
 * Details : Checks for collision between car and other objects in the world
 *
 */
#include "CheckCollision.h"

//
// Finds the pixel value of the world ground at the give coordinates
// and based on it's value it updates the crash status or Score
//
void SetCollisionAction(WorldBlock WBlocks[], uint16_t Px, uint16_t Py, CollisionEvent *CollSts) {

	// Pixel
	uint16_t Pixel = 0x32D0; // colour of road

	// shifting the origin after sidewalk
	Px = Px - SW_WIDTH;

	// Find which of the three boxes of the WorldBlocks the point falls in
	uint8_t Box = Px >> 6;	// Px divide by 64

	// X value relative to the obstacle box
	Px = Px - Box*OB_SIDE;

	// give the ObsType index
	uint8_t ObsId = Box;

	// bits in box represent the position
	Box = (1 << Box);

	// flag to check if car collided with obstacle or coin
	bool CollType = false; // false : Coin true : Obstacle

	// To track the block id where point lies
	bool WBlockColl = false; // false - collision happened in WBlocks[1]

	// Check in WBlock1
	if(Py >= WBlocks[1].OffsetY) {
		// if box has obstacles
		Py = Py - WBlocks[1].OffsetY;
		if(Box & WBlocks[1].ObsPlaceType) {
			Pixel = Obstacles[WBlocks[1].ObsType[ObsId]][Py*64 + Px];
			CollType = true;
		}
		// if box has coins
		else if(Box & WBlocks[1].CoinPlaceType) {
			Pixel = Coin[Py*64 + Px];
		}
	}
	// Check in WBlock2
	else {

		WBlockColl = true;

		// if box has obstacles
		if(Box & WBlocks[2].ObsPlaceType) {
			Py = Py - WBlocks[2].OffsetY;
			Pixel = Obstacles[WBlocks[2].ObsType[ObsId]][Py*64 + Px];
			CollType = true;
		}
		// if box has coins
		else if(Box & WBlocks[1].CoinPlaceType) {
			Pixel = Coin[Py*64 + Px];
		}
	}

	// A point of car is not on road
	if(Pixel != 0x32D0) {
		if(CollType) {
			CollSts->Crash = true;
		}
		// if collision is with coin
		else {
			CollSts->Crash = false;
			CollSts->Score++;

			// remove the coin from the block
			if(WBlockColl) { // remove coin from WBlocks[1]
				WBlocks[1].CoinPlaceType = (~Box) & WBlocks[1].CoinPlaceType;
			}
			else {
				WBlocks[2].CoinPlaceType = (~Box) & WBlocks[2].CoinPlaceType;
			}
		}
	}

}
