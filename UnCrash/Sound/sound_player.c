#include "sound_player.h"

void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

void play_sound(const struct SoundParameters *params) {
    // Initialize sound
    //Drivers
    PWM8731Ctx_t audio;
    PHPSGPIOCtx_t gpio;
    PHPSI2CCtx_t   i2c;

    //Initialise Drivers
    exitOnFail(HPS_GPIO_initialise(LSC_BASE_ARM_GPIO, ARM_GPIO_DIR, ARM_GPIO_I2C_GENERAL_MUX, 0, &gpio), ERR_SUCCESS);
    exitOnFail(HPS_I2C_initialise(LSC_BASE_I2C_GENERAL, I2C_SPEED_STANDARD, &i2c), ERR_SUCCESS);
    exitOnFail(WM8731_initialise(LSC_BASE_AUDIOCODEC, i2c, &audio), ERR_SUCCESS);
    // Code to initialize the sound, setting up phase accumulator, etc.
    // You may use params->amplitude, params->increment, and params->duration
    // Calculate phase increment based on provided increment value
    double phaseIncrement = params->increment;
    // Set initial phase to 0
    double phase = 0.0;

    //Clear both FIFOs
    WM8731_clearFIFO(audio, true,true);
    //Initialise Phase Accumulator
    unsigned int sampleRate = 48000;
    WM8731_getSampleRate(audio, &sampleRate);
    // Loop to play sound for the specified duration
    for (unsigned int i = 0; i < params->duration * 48000 / 1000; i++) {
                // Generate audio sample using sin function
        double amplitude = params->amplitude * sin(phase);
        // Write audio sample to left and right channels of the codec
        WM8731_writeSample(audio, (signed int)amplitude, (signed int)amplitude);

        // Update phase for next sample
        phase += phaseIncrement;

        // Ensure phase is within the range [0, 2π]
        while (phase >= 2 * M_PI){
            phase -= 2 * M_PI;
    }
    }
    // Reset the watchdog
    HPS_ResetWatchdog();
}
