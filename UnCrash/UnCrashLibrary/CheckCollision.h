/*
 * File: CheckCollision.h
 *
 * Details : Detects collisions between the player's car
 * and other objects within the game world.
 *
 * Author: Santosh K S
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef CHECKCOLLISION_H_
#define CHECKCOLLISION_H_

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

#include "Sprites.h" // Game sprite dimensions and game world definition

// Maximum score achievable in game
#define MAX_SCORE 9999

//
// Structure: CollisionEvent
// Details: Stores the action of collision event: crash or collect coin
//
typedef struct CollisionEvent {
	bool Crash;		// True if car crashes with obstacles
	uint16_t Score;	// Keeps track of the coins collected
} CollisionEvent;

//
// Function: SetCollisionAction
// Details: Determines the pixel value of the game world at the specified coordinates,
// updating the crash status or score based on its value.
// Arguments: World blocks, x-y coordinates, collision status
// Return: Void. Updates the collision status value passed in argument.
//
void SetCollisionAction(WorldBlock WBlocks[], uint16_t Px, uint16_t Py, CollisionEvent *CollSts);

//
// Function: CheckCollision
// Details: Verifies if each corner of the car collides with obstacles
// or coins, updating the score in case of a coin collision and setting
// the crash status upon collision with obstacles.
// Arguments: World blocks, car position and collision status
// Return: Void. Updates the collision status value passed in argument.
//
void CheckCollision(WorldBlock WBlocks[], uint16_t CarPosX, CollisionEvent *CollSts);

#endif /* CHECKCOLLISION_H_ */
