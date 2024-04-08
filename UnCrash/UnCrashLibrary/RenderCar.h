#ifndef RENDERCAR_H_
#define RENDERCAR_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sprites.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "DE1SoC_Addresses/DE1SoC_Addresses.h"

#define CAR_POS_Y  208u			// Car top left Y position is fixed
#define CAR_INIT_POS_X 112u		// Car top left X position at the start

//
// Renders the Car on LT24 screen at the given top right x and y position
//
void RenderCar(uint16_t PosX, uint16_t PosY, bool Crash, PLT24Ctx_t lt24);

//
// Shifts the position of the car in x-axis on key press
// returns the car's top left x position
int16_t MoveCar(uint8_t ShiftX, bool Crash, PLT24Ctx_t lt24);

#endif /* RENDERCAR_H_ */
