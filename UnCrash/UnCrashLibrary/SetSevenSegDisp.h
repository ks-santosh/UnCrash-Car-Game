/*
 * File: SetSevenSegDisp.h
 *
 * Details : Declaration for seven-segment display functions
 *
 */

#ifndef SEVENSEGDISP_H_
#define SEVENSEGDISP_H_

#include <stdint.h>
#include <stdbool.h>

//
// Initialises seven-segment displays with default values
//
void InitialiseSevenSeg();

//
// Displays a digit on a particular seven-segment display
//
void SetSingleSevenSeg(uint8_t Disp, uint8_t Num);

//
// Displays a four digit number on seven-segment display
//
void SetSevenSegDisp(uint16_t Num);

#endif /* SEVENSEGDISP_H_ */
