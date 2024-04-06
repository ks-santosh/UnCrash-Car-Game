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

void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

void InitWorldBlock(WorldBlock WBlocks[]) {
	// Block 0
	WBlocks[0].ObsPlaceType = 5;
	WBlocks[0].ObsType1 = 1;
	WBlocks[0].ObsType2 = 2;
	WBlocks[0].CoinPlaceType = 0;
	WBlocks[0].Start = 0;
	WBlocks[0].End = OB_SIDE - 1;
	WBlocks[0].OffsetY = 4*OB_SIDE;

	// Block 1
	WBlocks[1].ObsPlaceType = 5;
	WBlocks[1].ObsType1 = 3;
	WBlocks[1].ObsType2 = 4;
	WBlocks[1].CoinPlaceType = 0;
	WBlocks[1].Start = 0;
	WBlocks[1].End = OB_SIDE - 1;
	WBlocks[1].OffsetY = 3*OB_SIDE;

	// Block 2
	WBlocks[2].ObsPlaceType = 5;
	WBlocks[2].ObsType1 = 5;
	WBlocks[2].ObsType2 = 6;
	WBlocks[2].CoinPlaceType = 0;
	WBlocks[2].Start = 0;
	WBlocks[2].End = OB_SIDE - 1;
	WBlocks[2].OffsetY = 2*OB_SIDE;

	// Block 3
	WBlocks[3].ObsPlaceType = 5;
	WBlocks[3].ObsType1 = 7;
	WBlocks[3].ObsType2 = 0;
	WBlocks[3].CoinPlaceType = 0;
	WBlocks[3].Start = 0;
	WBlocks[3].End = OB_SIDE - 1;
	WBlocks[3].OffsetY = OB_SIDE;

	// Block 4
	WBlocks[4].ObsPlaceType = 5;
	WBlocks[4].ObsType1 = 1;
	WBlocks[4].ObsType2 = 2;
	WBlocks[4].CoinPlaceType = 0;
	WBlocks[4].Start = 0;
	WBlocks[4].End = OB_SIDE -1;
	WBlocks[4].OffsetY = 0;

	// Block 5
	WBlocks[5].ObsPlaceType = 5;
	WBlocks[5].ObsType1 = 3;
	WBlocks[5].ObsType2 = 4;
	WBlocks[5].CoinPlaceType = 0;
	WBlocks[5].Start = OB_SIDE;
	WBlocks[5].End = OB_SIDE;
	WBlocks[5].OffsetY = 0;

}

//
// Main Function
// =============
int main(void) {
    //Main Run Loop

	// Game Title Screen
	// Game Settings
	// Game Start
	// Game running

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

	/*for(int i = 0; i < 5; i++)
	{
		HPS_ResetWatchdog();
		RenderWorldBlock(&blocks[i], lt24);
	}*/

    while (1) {
    	HPS_ResetWatchdog(); //Just reset the watchdog.
        RenderWorld(WBlocks, lt24, 1);
    }
}
