#ifndef RENDERCAR_H_
#define RENDERCAR_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"

//
// Renders the Car on LT24 screen at the given top right x and y position
//
void RenderCar(uint16_t PosX, uint16_t PosY, bool Crash, PLT24Ctx_t lt24);

#endif /* RENDERCAR_H_ */
