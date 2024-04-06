//car_position.c file
#include "car_position.h"

// Peripheral base addresses.
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;

// Define a structure to represent car position
typedef struct {
    int x;
    int y;
} CarPosition;

// Define a structure to represent LT24 display context
typedef struct {
    PLT24Ctx_t lt24;
    int width;
    int height;
} LT24Display;

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