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


#include "car_position.h"
#include "Test.h" // Assuming Test.h contains the image data

#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"

#include <stdlib.h>

void exitOnFail(signed int status, signed int successStatus) {
    if (status != successStatus) {
        exit((int)status); // Add breakpoint here to catch failure
    }
}

int main(void) {
    PLT24Ctx_t lt24;
    int image_x = 50; // Initial x position of the image
    int image_y = 50; // Initial y position of the image
    
    // Initialize the LCD Display
    exitOnFail(LT24_initialize_display(&lt24), ERR_SUCCESS);
    HPS_ResetWatchdog();

    // Display the image
    exitOnFail(LT24_display_image(lt24, Test, 120, 160, image_x, image_y), ERR_SUCCESS);

    // Main Run Loop
    while (1) {
        // Handle car movement based on key presses
        handle_car_movement(lt24, Test, 120, 160, &image_x, &image_y);
        
        HPS_ResetWatchdog(); // Just reset the watchdog
    }
}