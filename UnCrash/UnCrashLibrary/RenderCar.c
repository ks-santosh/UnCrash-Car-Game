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
