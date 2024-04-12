/*
 * File: PlayAudio.h
 *
 * Details : Declarations of functions that plays sound on WM8731 chip.
 *
 */

#ifndef PLAYAUDIO_H_
#define PLAYAUDIO_H_


#include <stdint.h>
#include <stdbool.h>

// Libraries to set up audio drivers
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "HPS_GPIO/HPS_GPIO.h"
#include "HPS_I2C/HPS_I2C.h"
#include "FPGA_PIO/FPGA_PIO.h"
#include "Util/macros.h"

//Include Floating Point Math Libraries
#include <math.h>

// Contains music
#include "Sounds.h"

//
// Plays two tones one after another
//
void PlayCoinSound(PWM8731Ctx_t audio);

//
// Plays music
//
void PlayMusic(PWM8731Ctx_t audio);

#endif /* PLAYAUDIO_H_ */
