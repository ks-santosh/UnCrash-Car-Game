/*
 * Sprites.h
 *
 * Sprites used in the game
 */

#ifndef SPRITES_H_
#define SPRITES_H_

//
// Sets the design and placement of game world's basic blocks
//
typedef struct WorldBlock {
	uint8_t ObsPlaceType;	// Obstacle placement type
	uint8_t CoinPlaceType;	// Coin placement type
	uint8_t ObsType[3];		// select three obstacles
	uint8_t Start;			// starting row to render from
	uint8_t End;			// end row to render till
	uint16_t OffsetY;		// The y-axis point on LCD to draw from
} WorldBlock;

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


extern const unsigned short SidewalkLeft[1536];
extern const unsigned short SidewalkRight[1536];

extern const unsigned short Obstacle1[4096];
extern const unsigned short Obstacle2[4096];
extern const unsigned short Obstacle3[4096];
extern const unsigned short Obstacle4[4096];
extern const unsigned short Obstacle5[4096];
extern const unsigned short Obstacle6[4096];
extern const unsigned short Obstacle7[4096];
extern const unsigned short Obstacle8[4096];

extern const unsigned short Road[4096];

extern const unsigned short *const Obstacles[8];

extern const unsigned short CarCrashed[512];
extern const unsigned short Car[512];

extern const unsigned short Coin[4096];

#endif /* SPRITES_H_ */
