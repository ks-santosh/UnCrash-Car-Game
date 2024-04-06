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