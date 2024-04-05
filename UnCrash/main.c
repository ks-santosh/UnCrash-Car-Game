/*
 * File: main.c
 *
 * Details : UnCrash, a game rendered on LT24 in which you have to
 * drive a car avoiding obstacles and collecting coins. The score is
 * shown on seven segment displays on DE1-SoC.
 *
 * Created on: 04 April 2024
 *      Author: Santosh K S
 * Updated on: 04 April 2024
 *      Author: Santosh K S
 */


#include "DE1SoC_Addresses/DE1SoC_Addresses.h"
#include "DE1SoC_IRQ/DE1SoC_IRQ.h"
#include "HPS_GPIO/HPS_GPIO.h"
#include "FPGA_PIO/FPGA_PIO.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"


typedef struct {
    // Driver contexts:
    PFPGAPIOCtx_t hex0to3; // using 7 seg driver to test
    PFPGAPIOCtx_t keys; // using buttons driver for creating interrupts
    PHPSGPIOCtx_t hpsIo; // using IO gpio pins
    // Value returned from interrupt:
    volatile unsigned int keyPressed;
} AppDrivers_t;


//
// Main Function
// =============
int main(void) {
    //Main Run Loop
    while (1) {
        HPS_ResetWatchdog(); //Just reset the watchdog.
    }
}
