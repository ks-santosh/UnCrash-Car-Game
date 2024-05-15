/*
 * File: RenderCar.c
 *
 * Details : Renders and moves the Car on LT24 screen to the given position.
 *
 * Author: Aakash Rao
 *
 */

// Header inclusion
#include "RenderCar.h"

//
// Function: RenderCar
// Details: Renders the Car on LT24 screen at the given top right x and y position
// Arguments: x, y position, crash status and LT24 driver context
// Return: Void.
//
void RenderCar(uint16_t PosX, uint16_t PosY, bool Crash, PLT24Ctx_t lt24) {

	// Pointer to pixel array of car's image
	const unsigned short *ShowCar = Car;

	// Display crashed car if crash status is set
	if(Crash) {
		ShowCar = CarCrashed;
	}

	// Render car bonnet
	LT24_copyFrameBuffer(lt24, ShowCar + 3, PosX+3, PosY, 10, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 18, PosX+2, PosY+1, 12, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 33, PosX+1, PosY+2, 14, 1);

	// Render car main body
	LT24_copyFrameBuffer(lt24, ShowCar + 48, PosX, PosY+3, 16, 26);

	// Render car boot
	LT24_copyFrameBuffer(lt24, ShowCar + 465, PosX+1, PosY+29, 14, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 482, PosX+2, PosY+30, 12, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 499, PosX+3, PosY+31, 10, 1);

}

//
// Function: MoveCar
// Details: Moves the car horizontally along the x-axis by a specified distance on kye press.
// Arguments: x-y position, horizontal shift value for car, LT24 driver context
// Return: Updated X position of the car
//
int16_t MoveCar(int16_t PrvPosX, uint8_t ShiftX, bool Crash, PLT24Ctx_t lt24) {

	int16_t PosX = PrvPosX;

	// Check for button press
	volatile unsigned int *KEY_ptr = (unsigned int *)LSC_BASE_KEYS;	// KEY buttons base

	// Set N to KEY[3:0] input value
	unsigned int N = *KEY_ptr & 0x0F;

	// If crash or left-right keys pressed simultaneously
	// don't update car's position.
	if((Crash) || ((N & 9u) == 9u)) {
		RenderCar(PosX, CAR_POS_Y, Crash, lt24);
		return PosX;
	}


	// Check which key is pressed
	if(N & 1u) {

		// Rove right if Key 0 pressed
		PosX = PrvPosX + ShiftX;
	}
	else if(N >> 3) {

		// Rove left if Key 3 pressed
		PosX = PrvPosX - ShiftX;
	}

	// If car moves onto the right sidewalk
	if(PosX > (LT24_WIDTH - SW_WIDTH - CAR_WIDTH)) {

		// Keep the car's position adjacent to the right sidewalk
		PosX = (LT24_WIDTH - SW_WIDTH - CAR_WIDTH);
	}
	// Else if car moves onto the left sidewalk
	else if(PosX < SW_WIDTH) {

		// Keep the car's position adjacent to the left sidewalk
		PosX = SW_WIDTH;
	}

	// Render car at the updated position
	RenderCar(PosX, CAR_POS_Y, Crash, lt24);

	// Return the updated position
	return PosX;
}
