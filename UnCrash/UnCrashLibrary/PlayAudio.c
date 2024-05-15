/*
 * File: PlayAudio.c
 *
 * Details: Triggers sound playback on the WM8731
 * chip in response to game events.
 *
 * Author: Nikhilesh Bhaskar
 *
 */

// Header inclusion
#include "PlayAudio.h"

//
// Function: PlayCoinSound
// Details: Plays two tones one after another
// Arguments: Audio driver context
// Return: Void.
//
void PlayCoinSound(PWM8731Ctx_t audio) {

	// Sound duration
	const int32_t Duration = 10000;

	// To store space of FIFO channels
	uint32_t FifoSpace;

	// Get the sampleRate of the DAC
	unsigned int sampleRate;
	WM8731_getSampleRate(audio, &sampleRate);

	// Initialise Phase Accumulator
	double phase  = 0.0;  							// Phase accumulator
	double inc1   = 988.0 * M_2PI / sampleRate;   	// Phase increment 1 for Tone 1
	double inc2   = 1319.0 * M_2PI / sampleRate;	// Phase increment 2 for Tone 2
	double ampl   = 8388608.0;						// Tone amplitude (i.e. volume)
	int32_t audio_sample = 0;

	for(int32_t i = Duration; i > 0; i--) {

		// Always check the FIFO Space before writing to the left/right channel pointers
		WM8731_getFIFOSpace(audio, &FifoSpace);

		// If there is space in the write FIFO for both channels:
		if (FifoSpace > 0) {

			// Increment the phase
			if(i > Duration/2) {
				phase = phase + inc1; // Phase increment for later half of the duration
			}
			else {
				phase = phase + inc2; // Phase increment for initial half of the duration
			}

			//Ensure phase is wrapped to range 0 to 2Pi (range of sin function)
			while (phase >= M_2PI) {
				phase = phase - M_2PI;
			}

			// Calculate next sample of the output tone.
			audio_sample = (int32_t)( ampl * sin( phase ) );

			// Output tone to left and right channels.
			WM8731_writeSample(audio, audio_sample, audio_sample);

		}
	}

}

//
// Function: PlayMusic
// Details: Plays music from the audio file encoded
// in signed 32 bit integer
// Arguments: Audio driver context
// Return: Void.
//
void PlayMusic(PWM8731Ctx_t audio) {

	// Initialise the ARM A9 Private Timer
	volatile unsigned int *private_timer_value = (unsigned int *)(LSC_BASE_PRIV_TIM + 0x4);
	volatile unsigned int *private_timer_interrupt = (unsigned int *)(LSC_BASE_PRIV_TIM + 0xC);

	// Initialise timer values for audio playing speed control
	uint32_t TaskTimerValue = *private_timer_value;
	uint32_t CurrentTimerValue = *private_timer_value;

	// To store space of FIFO channels
	uint32_t FifoSpace;

	// Size of audio array
	uint32_t MusicSize = sizeof(MusicLoop)/sizeof(MusicLoop[0]);

	for(int32_t i = 0; i < MusicSize; i++) {

		// Timer value at the start of each iteration
		TaskTimerValue = *private_timer_value;

		//Always check the FIFO Space before writing to the left/right channel pointers
		WM8731_getFIFOSpace(audio, &FifoSpace);

		//If there is space in the write FIFO for both channels:
		if (FifoSpace > 0) {

			// Output tone to left and right channels.
			WM8731_writeSample(audio, MusicLoop[i], MusicLoop[i]);
		}

		// Current timer value
		CurrentTimerValue = *private_timer_value;

		// Loop until delay time is elapsed to create a blocking
		// delay. This will control the audio playback speed.
		while((TaskTimerValue - CurrentTimerValue) < SP_MUSIC) {

			// Current timer value
			CurrentTimerValue = *private_timer_value;
		}

	}

}
