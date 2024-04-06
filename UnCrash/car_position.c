//car_position.c file
#include "car_position.h"

// Peripheral base addresses.
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;


// Store the state of the keys last time we checked.
// This allows us to determine when a key is pressed, then released.
unsigned int key_last_state = 0;

unsigned int getPressedKeys() {
    // Store the current state of the keys.
    unsigned int key_current_state = *key_ptr;

    // If the key was down last cycle, and is up now, mark as pressed.
    unsigned int keys_pressed = (~key_current_state) & (key_last_state);

    // Save the key state for next time, so we can compare the next state to this.
    key_last_state = key_current_state;

    // Return result.
    return keys_pressed;
}

void handle_car_movement(CarPosition *carPos, LT24Display *display) {
    unsigned int keys_pressed = getPressedKeys();

    // Test if each key has been pressed in turn, carry out action if so.
    if (keys_pressed & 0x1) {
        // If KEY0 was pressed, move the car image towards the right (increase x position)
        (carPos->x) += 10; // You may adjust the value as needed for desired movement speed
    } else if (keys_pressed & 0x2) {
        // If KEY1 was pressed, move the car image towards the left (decrease x position)
        (carPos->x) -= 10; // You may adjust the value as needed for desired movement speed
    }
    // Display the updated car position
    LT24_display_image(display->lt24, Test, display->width, display->height, carPos->x, carPos->y);
}

int initialize_display(LT24Display *display) {
    return LT24_initialize_display(&(display->lt24));
}

int display_image(LT24Display *display, const unsigned short *image, int x, int y) {
    return LT24_display_image(display->lt24, image, display->width, display->height, x, y);
}