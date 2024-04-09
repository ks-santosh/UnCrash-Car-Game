/*
 * Sprites.h
 *
 * Sprites used in the game
 */

#ifndef SPRITES_H_
#define SPRITES_H_

// Sidewalk Dimensions
#define SW_WIDTH 24u
#define SW_HEIGHT 320u

// Obstacle Dimensions
#define OB_SIDE 64u

// Car dimensions
#define CAR_HEIGHT 32u
#define CAR_WIDTH 16u

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
