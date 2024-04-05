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

//Key Released Interrupt Displays Last Button Released
__irq void pushbuttonISR(HPSIRQSource interruptID, void* param, bool* handled) {
    //Return failure if context is NULL pointer.
    if (param == NULL) return;
    //Cast param to expected type
    AppDrivers_t* pDrivers = (AppDrivers_t*)param;
    //Read the Push-button interrupt register, and clear the flags
    unsigned int press;
    FPGA_PIO_getInterruptFlags(pDrivers->keys, &press, 0xF, true);
    //Update list of key presses received
    // - this is an example of how you can return values from an interrupt
    //   routine.
    pDrivers->keyPressed |= press;
    //IRQ Handled
    *handled = true;
    //Reset watchdog.
    HPS_ResetWatchdog();
}

//
// Main Function
// =============
int main(void) {
    //Main Run Loop
	// Keep track of all our device drivers in a friendly structure
	static AppDrivers_t drivers = {0};

	// Initialise drivers
	FPGA_PIO_initialise(LSC_BASE_KEYS, LSC_CONFIG_KEYS, &drivers.keys);
	FPGA_PIO_initialise(LSC_BASE_7SEG_0to3, LSC_CONFIG_7SEG, &drivers.hex0to3);
	//Set HPS LED low
		    HPS_GPIO_setOutput(drivers.hpsIo, 0, ARM_GPIO_HPS_LED);

		    //Initialise IRQs
		    HPS_IRQ_initialise(false,NULL);
		    HPS_ResetWatchdog();

		    // Register interrupt handler for keys
		    HPS_IRQ_registerHandler(IRQ_LSC_KEYS, pushbuttonISR, &drivers);
		    // Configure Push Buttons to interrupt on press
		    FPGA_PIO_setInterruptEnable(drivers.keys, 0xF, 0xF); // Enable interrupts for all four KEYs
		    HPS_ResetWatchdog();
		    //Finally we enable the interrupts
		    HPS_IRQ_globalEnable(true);

		    	    //Do nothing in the run loop but reset the watchdog.
		    	    //Notice how the light blinks anyway.
		    	    while(1) {
		    	        //With interrupts enabled, we can also save power by
		    	        //putting the processor to sleep, until an interrupt
		    	        //occurs.
		    	        //You don't have to do this if you have other things
		    	        //to do in the main run loop.
		    	        __asm("WFI");
		    	        //Reset watchdog.
		    	        HPS_ResetWatchdog();
		    	        //Check if any keys were pressed. We temporarily disable
		    	        //interrupts while we are reading the shared data value
		    	        HpsErr_t wasDisabled = HPS_IRQ_globalEnable(false);
		    	        unsigned int keyPressed = drivers.keyPressed; // Read bit map of pressed keys
		    	        drivers.keyPressed = 0;                       // Clear list for next time.
		    	        HPS_IRQ_globalEnable(wasDisabled != ERR_SKIPPED);
		    	        //Now do something to handle the key presses
		    	        if (keyPressed) {
		    	            unsigned int hexVal;
		    	            unsigned char* hexValPtr = (unsigned char*)&hexVal;
		    	            //Prepare to display 1 or 0 on 7-seg corresponding to whichever keys are pressed.
		    	            for (unsigned int i = 0; i < 4; i++) {
		    	                hexValPtr[i] = (keyPressed & (1 << i)) ? 0x06 : 0x3F;
		    	            }
		    	            // Display on 7-seg LEDs
		    	            FPGA_PIO_setOutput(drivers.hex0to3, hexVal, UINT32_MAX);
		    	        }
		    	    }
    while (1) {
        HPS_ResetWatchdog(); //Just reset the watchdog.
    }
}
