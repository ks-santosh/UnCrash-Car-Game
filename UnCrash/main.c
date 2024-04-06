// File: main.c

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
    CarPosition carPos = {50, 50}; // Initial position of the car
    LT24Display display = {{0}, 120, 160}; // Initialize LT24 display context

    // Initialize the LCD Display
    exitOnFail(initialize_display(&display), ERR_SUCCESS);
    HPS_ResetWatchdog();

    // Display the image
    exitOnFail(display_image(&display, Test, carPos.x, carPos.y), ERR_SUCCESS);

}