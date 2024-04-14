/*
 * File: RenderCar.c
 *
 * Details : Renders the Car on LT24 screen at the given position
 *
 */

#include "RenderCar.h"

//
// Renders the Car on LT24 screen at the given top right x and y position
//
void RenderCar(uint16_t PosX, uint16_t PosY, bool Crash, PLT24Ctx_t lt24) {

	const unsigned short *ShowCar = Car;

	if(Crash) {
		ShowCar = CarCrashed;
	}

	// render car bonnet
	LT24_copyFrameBuffer(lt24, ShowCar + 3, PosX+3, PosY, 10, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 18, PosX+2, PosY+1, 12, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 33, PosX+1, PosY+2, 14, 1);

	// render car main body
	LT24_copyFrameBuffer(lt24, ShowCar + 48, PosX, PosY+3, 16, 26);

	// render car boot
	LT24_copyFrameBuffer(lt24, ShowCar + 465, PosX+1, PosY+29, 14, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 482, PosX+2, PosY+30, 12, 1);
	LT24_copyFrameBuffer(lt24, ShowCar + 499, PosX+3, PosY+31, 10, 1);


}

//
// Shifts the position of the car in x-axis on key press
//
int16_t MoveCar(int16_t PrvPosX, uint8_t ShiftX, bool Crash, PLT24Ctx_t lt24) {

	int16_t PosX = PrvPosX;

	// Check for button press
	volatile unsigned int *KEY_ptr = (unsigned int *)LSC_BASE_KEYS;	// KEY buttons base

	// Set N to KEY[3:0] input value
	unsigned int N = *KEY_ptr & 0x0F;

	if((Crash) || ((N & 9u) == 9u)) {
		RenderCar(PosX, CAR_POS_Y, Crash, lt24);
		return PosX;
	}


	// Check which key is pressed
	if(N & 1u) {
		// move right
		PosX = PrvPosX + ShiftX;
	} else if(N >> 3) {
		PosX = PrvPosX - ShiftX;
	}

	// keep the position in range
	if(PosX > (LT24_WIDTH - SW_WIDTH - CAR_WIDTH)) {
		PosX = (LT24_WIDTH - SW_WIDTH - CAR_WIDTH);
	}
	else if(PosX < SW_WIDTH) {
		PosX = SW_WIDTH;
	}

	RenderCar(PosX, CAR_POS_Y, Crash, lt24);

	return PosX;
}
