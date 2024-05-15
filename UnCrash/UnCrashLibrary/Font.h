/*
 * File: Font.h
 *
 * Details : Defines structure and width of each character in the font image.
 *
 * Author: Santosh K S
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef FONT_H_
#define FONT_H_

// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

// Font's minimum height
#define FONT_HEIGHT 5

// Array of array of alphabets' pixel
extern const uint8_t *const Alphabet[26];

// Stores the pixel width of each alphabet
extern const uint8_t AlWidth[26];

// Array of array of digits' pixel
extern const uint8_t *const Digits[10];

// Stores the pixel width of each digit
extern const uint8_t DiWidth[10];

#endif /* FONT_H_ */
