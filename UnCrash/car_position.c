#include "car_position.h"

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

void handle_car_movement(CarPosition *carPos, LT24Display *display, const unsigned short *image) {
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
    LT24_copyFrameBuffer(&(display->lt24), image, carPos->x, carPos->y, display->width, display->height);
}

int initialize_display(LT24Display *display, volatile unsigned char *gpio_base, volatile unsigned char *lt24_base) {
    display->gpio_base = gpio_base;
    display->lt24_base = lt24_base;
    return LT24_initialise(&(display->lt24), gpio_base, lt24_base);
}

int display_image(LT24Display *display, const unsigned short *image, int x, int y) {
    return LT24_copyFrameBuffer(&(display->lt24), image, x, y, display->width, display->height);
}
