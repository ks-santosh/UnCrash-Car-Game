#include "switches.h"

volatile unsigned int *SW_ptr = (unsigned int *)0xFF200040;

unsigned int read_switches() {
    return *SW_ptr;
}
