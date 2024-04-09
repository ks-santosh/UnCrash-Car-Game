#include "sound.h"
#include <math.h>

// Define sound parameters
const struct SoundParameters star_sound_params = {
    .amplitude = 10000000.0,
    .increment = 1000.0 * M_2PI / 48000,
    .duration = 500 // 0.5 sec
};

const struct SoundParameters car_sound_params = {
    .amplitude = 8388608.0,
    .increment = 440.0 * M_2PI / 48000, // sample rate assumed 48000
    .duration = 0 // indefinite
};

const struct SoundParameters car_crash_params = {
    .amplitude = 100000000.0,
    .increment = 10000.0 * M_2PI / 48000,
    .duration = 3000 // 3 sec
};
