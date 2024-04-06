#ifndef CAR_POSITION_H
#define CAR_POSITION_H

#include "DE1SoC_LT24/DE1SoC_LT24.h"

// Function prototypes
int LT24_initialize_display(PLT24Ctx_t *lt24);
int LT24_display_image(PLT24Ctx_t lt24, const unsigned short *image, int width, int height, int x, int y);

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

#endif /* CAR_POSITION_H */