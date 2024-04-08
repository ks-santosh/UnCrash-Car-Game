// car_position.h file
#ifndef CAR_POSITION_H
#define CAR_POSITION_H

#include "DE1SoC_Addresses/DE1SoC_Addresses.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"
#include <stdlib.h>

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
    volatile unsigned char *gpio_base;
    volatile unsigned char *lt24_base;
} LT24Display;

// Function prototypes
int initialize_display(LT24Display *display, volatile unsigned char *gpio_base, volatile unsigned char *lt24_base);
int display_image(LT24Display *display, const unsigned short *image, int x, int y);
void handle_car_movement(CarPosition *carPos, LT24Display *display, const unsigned short *image);
unsigned int getPressedKeys();

#endif /* CAR_POSITION_H */
