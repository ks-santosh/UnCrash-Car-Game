/*
 * File: RenderCar.h
 *
 * Details : Renders and moves the Car on LT24 screen at the given position.
 *
 * Author: Aakash Rao
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef RENDERCAR_H_
#define RENDERCAR_H_

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

#include "DE1SoC_LT24/DE1SoC_LT24.h" // LT24 display driver
#include "DE1SoC_Addresses/DE1SoC_Addresses.h" // Address definition of peripherals

#include "Sprites.h" // Game sprite dimensions and game world definition

//
// Function: RenderCar
// Details: Renders the Car on LT24 screen at the given top right x and y position
// Arguments: x, y position, crash status and LT24 driver context
// Return: Void.
//
void RenderCar(uint16_t PosX, uint16_t PosY, bool Crash, PLT24Ctx_t lt24);

//
// Function: MoveCar
// Details: Moves the car horizontally along the x-axis by a specified distance on key press.
// Arguments: x-y position, horizontal shift value for car, LT24 driver context
// Return: Updated X position of the car
//
int16_t MoveCar(int16_t PrvPosX, uint8_t ShiftX, bool Crash, PLT24Ctx_t lt24);

#endif /* RENDERCAR_H_ */
