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

//
// Finds the pixel value of the world ground at the give coordinates
// return pixel value
uint16_t FindPixelValue(WorldBlock WBlocks[], uint16_t Px, uint16_t Py);


#endif /* CHECKCOLLISION_H_ */
