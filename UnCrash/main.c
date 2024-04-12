/*
 * File: main.c
 *
 * Details : UnCrash, a game rendered on LT24 in which you have to
 * drive a car avoiding obstacles and collecting coins. The score is
 * shown on seven segment displays on DE1-SoC.
 *
 * Created on: 04 April 2024
 *      Author: Santosh K S
 * Updated on: 04 April 2024
 *      Author: Santosh K S
 */

#include <stdint.h>
#include <stdbool.h>

#include "DE1SoC_Addresses/DE1SoC_Addresses.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"
#include "UnCrashLibrary/RenderWorld.h"
#include "UnCrashLibrary/RenderCar.h"
#include "UnCrashLibrary/CheckCollision.h"
#include "UnCrashLibrary/SetSevenSegDisp.h"

void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

void InitWorldBlock(WorldBlock WBlocks[]) {
	// Block 0
	WBlocks[0].ObsPlaceType = 5;
	WBlocks[0].ObsType[0] = 0;
	WBlocks[0].ObsType[1] = 1;
	WBlocks[0].ObsType[2] = 2;
	WBlocks[0].CoinPlaceType = 2;
	WBlocks[0].Start = 0;
	WBlocks[0].End = OB_SIDE - 1;
	WBlocks[0].OffsetY = 4*OB_SIDE;

	// Block 1
	WBlocks[1].ObsPlaceType = 5;
	WBlocks[1].ObsType[0] = 3;
	WBlocks[1].ObsType[1] = 4;
	WBlocks[1].ObsType[2] = 5;
	WBlocks[1].CoinPlaceType = 2;
	WBlocks[1].Start = 0;
	WBlocks[1].End = OB_SIDE - 1;
	WBlocks[1].OffsetY = 3*OB_SIDE;

	// Block 2
	WBlocks[2].ObsPlaceType = 5;
	WBlocks[2].ObsType[0] = 6;
	WBlocks[2].ObsType[1] = 7;
	WBlocks[2].ObsType[2] = 0;
	WBlocks[2].CoinPlaceType = 2;
	WBlocks[2].Start = 0;
	WBlocks[2].End = OB_SIDE - 1;
	WBlocks[2].OffsetY = 2*OB_SIDE;

	// Block 3
	WBlocks[3].ObsPlaceType = 5;
	WBlocks[3].ObsType[0] = 1;
	WBlocks[3].ObsType[1] = 2;
	WBlocks[3].ObsType[2] = 3;
	WBlocks[3].CoinPlaceType = 2;
	WBlocks[3].Start = 0;
	WBlocks[3].End = OB_SIDE - 1;
	WBlocks[3].OffsetY = OB_SIDE;

	// Block 4
	WBlocks[4].ObsPlaceType = 5;
	WBlocks[4].ObsType[0] = 4;
	WBlocks[4].ObsType[1] = 5;
	WBlocks[4].ObsType[2] = 6;
	WBlocks[4].CoinPlaceType = 2;
	WBlocks[4].Start = 0;
	WBlocks[4].End = OB_SIDE -1;
	WBlocks[4].OffsetY = 0;

	// Block 5
	WBlocks[5].ObsPlaceType = 5;
	WBlocks[5].ObsType[0] = 7;
	WBlocks[5].ObsType[1] = 0;
	WBlocks[5].ObsType[2] = 1;
	WBlocks[5].CoinPlaceType = 2;
	WBlocks[5].Start = OB_SIDE;
	WBlocks[5].End = OB_SIDE;
	WBlocks[5].OffsetY = 0;

}

//
// Main Function
// =============
int main(void) {

	//Variables
	PLT24Ctx_t lt24;
	//Initialise the LCD Display.
	exitOnFail(
			LT24_initialise(LSC_BASE_GPIO_JP1,LSC_BASE_LT24HWDATA, &lt24), //Initialise LCD
			ERR_SUCCESS);                                                  //Exit if not successful
	HPS_ResetWatchdog();

	WorldBlock WBlocks[6];

	// Initialise the world blocks
	InitWorldBlock(WBlocks);
	uint16_t CarPosX;
	CollisionEvent CollSts = {.Crash = false , .Score = 0};

	uint16_t PrvScore = 0;


	InitialiseSevenSeg();

	LT24_copyFrameBuffer(lt24, GameStartScreen, 0, 0, LT24_WIDTH, LT24_HEIGHT);

	volatile unsigned int *KEY_ptr = (unsigned int *)LSC_BASE_KEYS;
	// Set N to KEY[3:0] input value
	unsigned int N = *KEY_ptr & 0x0F;

	while(1) {
		// reset watchdog timer
		HPS_ResetWatchdog();
		if(*KEY_ptr & 4u){
			break;
		}
	}

	while (1) {

    	// reset watchdog timer
    	HPS_ResetWatchdog(); //Just reset the watchdog.

    	// render the world
    	RenderWorld(WBlocks, lt24, 2);

    	// move the car on button press
        CarPosX = (uint16_t)MoveCar(2, CollSts.Crash,lt24);

        // check for crash or coins
        CheckCollision(WBlocks, CarPosX, &CollSts);

        // if crash detected break from the loop
        if(CollSts.Crash) {
        	break;
        }

        // if score updated display it on Seven-Segment
        if(PrvScore != CollSts.Score) {
        	SetSevenSegDisp(CollSts.Score);
        	PrvScore = CollSts.Score;
        }
    }


}
