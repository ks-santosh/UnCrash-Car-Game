/*
 * File: CheckCollision.h
 *
 * Details : Checks for collision between car and other objects in the world
 *
 */

#ifndef CHECKCOLLISION_H_
#define CHECKCOLLISION_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"

// Maximum score achievable in game
#define MAX_SCORE 9999

//
// Stores the action of collision event: crash or collect coin
//
typedef struct CollisionEvent {
	bool Crash;		// true if car crashes with obstacles
	uint16_t Score;	// keeps track of the coins collected
} CollisionEvent;

//
// Finds the pixel value of the world ground at the give coordinates
// and based on it's value it updates the crash status or Score
//
void SetCollisionAction(WorldBlock WBlocks[], uint16_t Px, uint16_t Py, CollisionEvent *CollSts);

//
// Checks if the points of car collides with obstacles or coin
//
void CheckCollision(WorldBlock WBlocks[], uint16_t CarPosX, CollisionEvent *CollSts);

#endif /* CHECKCOLLISION_H_ */
