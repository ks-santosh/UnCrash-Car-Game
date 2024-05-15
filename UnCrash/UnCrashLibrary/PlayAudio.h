/*
 * File: PlayAudio.h
 *
 * Details: Triggers sound playback on the WM8731
 * chip in response to game events.
 *
 * Author: Nikhilesh Bhaskar
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef PLAYAUDIO_H_
#define PLAYAUDIO_H_

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths
#include <math.h>			// Include Floating Point Math Libraries

// Libraries to set up audio drivers
#include "DE1SoC_Addresses/DE1SoC_Addresses.h" // Address definition of peripherals
#include "DE1SoC_WM8731/DE1SoC_WM8731.h" // Driver for the WM8731 Audio Controller
#include "HPS_GPIO/HPS_GPIO.h" // Driver for controlling HPS GPIO pins.
#include "HPS_I2C/HPS_I2C.h" // Driver for the HPS embedded I2C controller
#include "FPGA_PIO/FPGA_PIO.h" // Driver for writing to generic PIO controller
#include "Util/macros.h" // Provides some helpful macros.

// Audio library
#include "Sounds.h"	// Contains audio file


// Sets the speed of audio playback in timer value
#define SP_MUSIC 1200

//
// Function: PlayCoinSound
// Details: Plays two tones one after another
// Arguments: Audio driver context
// Return: Void.
//
void PlayCoinSound(PWM8731Ctx_t audio);

//
// Function: PlayMusic
// Details: Plays music from the audio file encoded
// in signed 32 bit integer
// Arguments: Audio driver context
// Return: Void.
//
void PlayMusic(PWM8731Ctx_t audio);

#endif /* PLAYAUDIO_H_ */
