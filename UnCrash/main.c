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
#include "UnCrashLibrary/RenderText.h"

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


	// Game Variables
	WorldBlock WBlocks[6];	// Stores game block configurations
	CollisionEvent CollSts;	// Collision event status
	uint16_t CarPosX;		// Tracks car current position
	uint16_t PrvScore = 0;	// Previous score to track increment in score
	uint8_t CarShiftX = 5;	// car left-right shift by position if key pressed
	uint8_t WorldShiftY = 3;// world shift down position every iteration

	// Game Main Loop
	while(1) {

		//Initialise the Game world
		InitWorldBlock(WBlocks);
		InitialiseSevenSeg();
		LT24_copyFrameBuffer(lt24, GameStartScreen, 0, 0, LT24_WIDTH, LT24_HEIGHT);
		CollSts.Crash = false;
		CollSts.Score = 0;
		CarPosX = CAR_INIT_POS_X;
		HPS_ResetWatchdog();

		volatile unsigned int *KEY_ptr = (unsigned int *)LSC_BASE_KEYS;

		// Check for Key2 press
		while(1) {

			if(*KEY_ptr & 4u){
				break;
			}

			// reset watchdog timer
			HPS_ResetWatchdog();
		}

		// Play music before game begins
		PlayMusic(audio);

		while (1) {

			// reset watchdog timer
			HPS_ResetWatchdog(); //Just reset the watchdog.

			// render the world
			RenderWorld(WBlocks, lt24, WorldShiftY);

			// move the car on button press
			CarPosX = (uint16_t)MoveCar((int16_t)CarPosX, CarShiftX, CollSts.Crash,lt24);

			// check for crash or coins
			CheckCollision(WBlocks, CarPosX, &CollSts);

			// if crash detected break from the loop
			if(CollSts.Crash) {
				break;
			}

			// if score updated display it on Seven-Segment
			if(PrvScore != CollSts.Score) {
				SetSevenSegDisp(CollSts.Score);

				// Play coin sound effect
				PlayCoinSound(audio);

				PrvScore = CollSts.Score;

				// game ends if max score achieved
				if(CollSts.Score == MAX_SCORE) {
					break;
				}
			}
		}

		// Play music after game ends
		PlayMusic(audio);

		// Show game end screen
		RenderGrayScreen(WBlocks, lt24);
		MoveCar((int16_t)CarPosX, 0, CollSts.Crash, lt24);
		SetScreenText(CollSts.Score, lt24);

		// Check for Key2 press
		while(1) {

			if(*KEY_ptr & 4u){
				break;
			}

			// reset watchdog timer
			HPS_ResetWatchdog();
		}

		// Play music before changing screen
		PlayMusic(audio);

	} // Game Main Loop end
}
