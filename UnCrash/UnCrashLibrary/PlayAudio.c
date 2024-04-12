/*
 * File: PlayAudio.c
 *
 * Details : Plays sound on WM8731 chip when a game event occurs.
 *
 */

#include "PlayAudio.h"

//
// Plays two tones one after another
//
void PlayCoinSound(PWM8731Ctx_t audio) {

	// Sound duration
	const int32_t Duration = 10000;

	// To store space of FIFO channels
	uint32_t FifoSpace;

	// Get the sampleRate of the DAC
	unsigned int sampleRate;
	WM8731_getSampleRate(audio, &sampleRate);

	//Initialise Phase Accumulator
	double phase  = 0.0;  							// Phase accumulator
	double inc1   = 988.0 * M_2PI / sampleRate;   	// Phase increment 1
	double inc2   = 1319.0 * M_2PI / sampleRate;	// Phase increment 2
	double ampl   = 8388608.0;						// Tone amplitude (i.e. volume)
	int32_t audio_sample = 0;

	for(int32_t i = Duration; i > 0; i--) {

		//Always check the FIFO Space before writing to the left/right channel pointers
		WM8731_getFIFOSpace(audio, &FifoSpace);

		//If there is space in the write FIFO for both channels:
		if (FifoSpace > 0) {

			//Increment the phase
			if(i > Duration/2) {
				phase = phase + inc1;
			}
			else {
				phase = phase + inc2;
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
// Plays music
//
void PlayMusic(PWM8731Ctx_t audio) {

	// To store space of FIFO channels
	uint32_t FifoSpace;

	uint32_t MusicSize = sizeof(MusicLoop)/sizeof(MusicLoop[0]);

	for(int32_t i = 0; i < MusicSize; i++) {

		//Always check the FIFO Space before writing to the left/right channel pointers
		WM8731_getFIFOSpace(audio, &FifoSpace);

		//If there is space in the write FIFO for both channels:
		if (FifoSpace > 0) {
			// Output tone to left and right channels.
			WM8731_writeSample(audio, MusicLoop[i], MusicLoop[i]);
		}

		// To create delay between every sample
		for(int8_t d=10; d>0;d--);
	}

}
