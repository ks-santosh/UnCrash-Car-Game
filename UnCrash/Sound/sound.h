
#ifndef SOUND_H
#define SOUND_H

struct SoundParameters {
    double amplitude;
    double increment;
    unsigned int duration; // in milliseconds
};

extern const struct SoundParameters star_sound_params;
extern const struct SoundParameters car_sound_params;
extern const struct SoundParameters car_crash_params;

#endif /* SOUND_H */