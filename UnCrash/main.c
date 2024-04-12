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
#include "UnCrashLibrary/PlayAudio.h"

void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}


//
// Main Function
// =============
int main(void) {

	//Driver Variables
	PLT24Ctx_t lt24;
	PFPGAPIOCtx_t leds;
	PWM8731Ctx_t audio;
	PHPSGPIOCtx_t gpio;
	PHPSI2CCtx_t   i2c;

	// Game Variables
	WorldBlock WBlocks[6];
	CollisionEvent CollSts = {.Crash = false , .Score = 0};

	//Initialise the LCD Display.
	exitOnFail(LT24_initialise(LSC_BASE_GPIO_JP1,LSC_BASE_LT24HWDATA, &lt24), ERR_SUCCESS);                                                  //Exit if not successful
	HPS_ResetWatchdog();

	//Initialise Drivers for Audio
	exitOnFail(FPGA_PIO_initialise(LSC_BASE_RED_LEDS,LSC_CONFIG_RED_LEDS, &leds), ERR_SUCCESS);
    exitOnFail(HPS_GPIO_initialise(LSC_BASE_ARM_GPIO, ARM_GPIO_DIR, ARM_GPIO_I2C_GENERAL_MUX, 0, &gpio), ERR_SUCCESS);
    exitOnFail(HPS_I2C_initialise(LSC_BASE_I2C_GENERAL, I2C_SPEED_STANDARD, &i2c), ERR_SUCCESS);
    exitOnFail(WM8731_initialise(LSC_BASE_AUDIOCODEC, i2c, &audio), ERR_SUCCESS);

    //Clear both FIFOs
    WM8731_clearFIFO(audio, true,true);

	//Initialise the Game world
	InitWorldBlock(WBlocks);

	uint16_t CarPosX;

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
        	PlayCoinSound(audio);
        	PrvScore = CollSts.Score;
        }

    }


}
