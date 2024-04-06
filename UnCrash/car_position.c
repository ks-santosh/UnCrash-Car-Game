//car_position.c file
#include "car_position.h"

// Peripheral base addresses.
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;

// Define a structure to represent car position
typedef struct {
    int x;
    int y;
} CarPosition;


