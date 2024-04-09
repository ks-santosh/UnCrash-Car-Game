#include "sound.h"
#include "sound_player.h"
#include "switches.h"

int main(void) {
    unsigned int switches;
    while (1) {
        switches = read_switches();
        if (switches & 0x1) {
            play_sound(&star_sound_params);
        } else if (switches & 0x2) {
            play_sound(&car_sound_params);
        } else if (switches & 0x4) {
            play_sound(&car_crash_params);
        }
    }
    //Finally reset the watchdog.
    HPS_ResetWatchdog();
}
