#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include "sound.h"
#include "DE1SoC_Addresses/DE1SoC_Addresses.h"
#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_GPIO/HPS_GPIO.h"
#include "HPS_I2C/HPS_I2C.h"
#include "FPGA_PIO/FPGA_PIO.h"
#include "Util/macros.h"

void play_sound(const struct SoundParameters *params);
void exitOnFail(signed int status, signed int successStatus);
#endif /* SOUND_PLAYER_H */
