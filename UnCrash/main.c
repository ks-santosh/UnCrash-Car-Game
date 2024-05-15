/*
 * File: main.c
 *
 * Details : Main source code of UnCrash game.
 * UnCrash is an engaging game designed to be rendered
 * on the LT24 display. Players control a car and navigate through
 * a dynamically generated environment, avoiding obstacles and
 * collecting coins along the way. The game's score, reflecting the
 * number of coins collected, is prominently displayed on the
 * seven-segment displays of the DE1-SoC board.
 *
 * Author: Santosh K S
 *
 */

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

// DE1SoC specific driver library
#include "DE1SoC_Addresses/DE1SoC_Addresses.h" // Address definition of peripherals
#include "DE1SoC_LT24/DE1SoC_LT24.h" // Driver for the LT24 Display Controller
#include "HPS_Watchdog/HPS_Watchdog.h" // HPS Watchdog driver
#include "HPS_usleep/HPS_usleep.h" // Timer based usleep driver

// UnCrash game library
#include "UnCrashLibrary/RenderWorld.h" // Sets game world
#include "UnCrashLibrary/RenderCar.h" // Renders car in the game
#include "UnCrashLibrary/CheckCollision.h" // Checks collision between sprites
#include "UnCrashLibrary/SetSevenSegDisp.h" // Sets score on Seven-Segment
#include "UnCrashLibrary/PlayAudio.h" // Plays game sounds
#include "UnCrashLibrary/RenderText.h" // Renders text over game

// Sets the speed of game play in A9 timer value
#define SP_GAME 10000000

//
// Function: exitOnFail
// Details: Checks if the functions ran successfully, exits otherwise.
// Arguments: LT24 driver or any function status and status for success
// Returns: exits the application
//
void exitOnFail(signed int status, signed int successStatus){
 	if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

//
// Function: main
// Details: UnCrash game engine
// Arguments: void
// Returns: exit status 0
//
int main(void) {

	// Driver Variables
	PLT24Ctx_t lt24;
	PFPGAPIOCtx_t leds;
	PWM8731Ctx_t audio;
	PHPSGPIOCtx_t gpio;
	PHPSI2CCtx_t   i2c;

	// Initialise the LCD Display.
	exitOnFail(LT24_initialise(LSC_BASE_GPIO_JP1,LSC_BASE_LT24HWDATA, &lt24), ERR_SUCCESS);                                                  //Exit if not successful

	HPS_ResetWatchdog(); // Reset watchdog timer

	// Initialise Drivers for Audio
	// Initialise FPGA PIO Driver
	exitOnFail(FPGA_PIO_initialise(LSC_BASE_RED_LEDS,LSC_CONFIG_RED_LEDS, &leds), ERR_SUCCESS);

	// Initialise HPS GPIO Driver
	exitOnFail(HPS_GPIO_initialise(LSC_BASE_ARM_GPIO, ARM_GPIO_DIR, ARM_GPIO_I2C_GENERAL_MUX, 0, &gpio), ERR_SUCCESS);

	// Initialise HPS GPIO Driver
	exitOnFail(HPS_I2C_initialise(LSC_BASE_I2C_GENERAL, I2C_SPEED_STANDARD, &i2c), ERR_SUCCESS);

	// Initialise Audio Codec
	exitOnFail(WM8731_initialise(LSC_BASE_AUDIOCODEC, i2c, &audio), ERR_SUCCESS);

    // Initialise the ARM A9 Private Timer
    volatile unsigned int *private_timer_load = (unsigned int *)(LSC_BASE_PRIV_TIM + 0x0);
    volatile unsigned int *private_timer_value = (unsigned int *)(LSC_BASE_PRIV_TIM + 0x4);
	volatile unsigned int *private_timer_control = (unsigned int *)(LSC_BASE_PRIV_TIM + 0x8);
	volatile unsigned int *private_timer_interrupt = (unsigned int *)(LSC_BASE_PRIV_TIM + 0xC);

	// Configure the ARM Private Timer
    // Set the "Load" value of the timer to max value:
	*private_timer_load      = 0xFFFFFFFF;

	// Set the "Prescaler" value to 0, Enable the timer (E = 1), Set Automatic reload
	// on overflow (A = 1), and disable ISR (I = 0)
	*private_timer_control   = (0 << 8) | (0 << 2) | (1 << 1) | (1 << 0);

	// Initialise timer values for game speed controls
	uint32_t TaskTimerValue = *private_timer_value;
	uint32_t CurrentTimerValue = *private_timer_value;

    // Clear both FIFOs
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

		// Initialise the Game world
		InitWorldBlock(WBlocks);

		// Initialise the seven segment display
		InitialiseSevenSeg();

		// Display game start screen
		LT24_copyFrameBuffer(lt24, GameStartScreen, 0, 0, LT24_WIDTH, LT24_HEIGHT);

		// Initialise game state variables
		CollSts.Crash = false; // Crash status is false
		CollSts.Score = 0; // Reset score
		CarPosX = CAR_INIT_POS_X; // Set car's starting position in game

		HPS_ResetWatchdog(); // Reset watchdog timer

		// Pointer to memory mapped peripheral - Keys
		volatile unsigned int *KEY_ptr = (unsigned int *)LSC_BASE_KEYS;

		// Loop until Key2 is not pressed
		while(1) {

			if(*KEY_ptr & 4u){
				break;
			}

			// Reset watchdog timer
			HPS_ResetWatchdog();
		} // Start game if Key2 is pressed

		// Play music before starting game
		PlayMusic(audio);

		// Game-play loop
		while (1) {

			// Get current timer value
			CurrentTimerValue = *private_timer_value;

			// Controls the speed of the game
			// Run game task if play task time is elapsed
			if((TaskTimerValue - CurrentTimerValue) >= SP_GAME) {

				// Timer value at the start of each iteration
				TaskTimerValue = *private_timer_value;

				// Reset watchdog timer
				HPS_ResetWatchdog();

				// Render the world
				RenderWorld(WBlocks, lt24, WorldShiftY);

				// Move the car on button press
				CarPosX = (uint16_t)MoveCar((int16_t)CarPosX, CarShiftX, CollSts.Crash,lt24);

				// Check for collision resulting in crash or coins
				CheckCollision(WBlocks, CarPosX, &CollSts);

				// If crash detected end the game
				if(CollSts.Crash) {
					break;
				}

				// If score updated display it on Seven-Segment
				if(PrvScore != CollSts.Score) {

					// Set score on seven-segment
					SetSevenSegDisp(CollSts.Score);

					// Play score update sound effect
					PlayCoinSound(audio);

					// Update previous score
					PrvScore = CollSts.Score;

					// Game ends if max score achieved
					if(CollSts.Score == MAX_SCORE) {
						break;
					}
				}
			} // Timed loop end

			// Clear the private timer interrupt flag if it is set
			if (*private_timer_interrupt & 0x1) {
				*private_timer_interrupt = 0x1;
			}

		} // Game-play loop end

		// Play music after game ends
		PlayMusic(audio);

		// Show game grayscale end screen
		RenderGrayScreen(WBlocks, lt24);

		// Show crashed car
		MoveCar((int16_t)CarPosX, 0, CollSts.Crash, lt24);

		// Display score on game screen
		SetScreenText(CollSts.Score, lt24);

		// Loop until Key1 not pressed
		while(1) {

			if(*KEY_ptr & 2u){
				break;
			}

			// Reset watchdog timer
			HPS_ResetWatchdog();

		} // Replay if Key1 is pressed

		// Play music before changing to start screen
		PlayMusic(audio);

	} // Game Main Loop end

} // Main function end
