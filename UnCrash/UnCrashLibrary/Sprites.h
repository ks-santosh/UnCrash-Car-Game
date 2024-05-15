/*
 * File: Sprites.c
 *
 * Details: RGB565 pixel value array of sprites used in the game.
 * Comprises of sidewalk, obstacles, coins, car and other images.
 * Has world block definitions and image dimensions.
 *
 * Author: Santosh K S
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef SPRITES_H_
#define SPRITES_H_

//
// Structure: WorldBlock
// Details: Sets the design and placement of game world's blocks
//
typedef struct WorldBlock {
	uint8_t ObsPlaceType;	// Obstacle placement type
	uint8_t CoinPlaceType;	// Coin placement type
	uint8_t ObsType[3];		// select three obstacles
	uint8_t Start;			// starting row to render from
	uint8_t End;			// end row to render till
	uint16_t OffsetY;		// The y-axis point on LCD to draw from
} WorldBlock;

// Colour of road
#define ROAD_COLOUR 0x32D0

// Sidewalk Dimensions
#define SW_WIDTH 24u
#define SW_HEIGHT 320u

// Obstacle Dimensions
#define OB_SIDE 64u

// Car dimensions
#define CAR_HEIGHT 32u
#define CAR_WIDTH 16u

// Car Position
#define CAR_POS_Y  208u			// Car top left Y position is fixed
#define CAR_INIT_POS_X 112u		// Car top left X position at the start

// Game start screen with instructions
extern const unsigned short GameStartScreen[76800];

// Sidewalk pixel array
extern const unsigned short SidewalkLeft[1536]; // Left sidewalk
extern const unsigned short SidewalkRight[1536]; // Right sidewalk

// Obstacle blocks pixel array. There are 8 types of obstacles
extern const unsigned short Obstacle1[4096];
extern const unsigned short Obstacle2[4096];
extern const unsigned short Obstacle3[4096];
extern const unsigned short Obstacle4[4096];
extern const unsigned short Obstacle5[4096];
extern const unsigned short Obstacle6[4096];
extern const unsigned short Obstacle7[4096];
extern const unsigned short Obstacle8[4096];

// Array of obstacle array
extern const unsigned short *const Obstacles[8];

// Car pixel array
extern const unsigned short CarCrashed[512]; // Crashed car pixel array
extern const unsigned short Car[512]; // Car image pixel array

// Coin block pixel array
extern const unsigned short Coin[4096];

#endif /* SPRITES_H_ */
