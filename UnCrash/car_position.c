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