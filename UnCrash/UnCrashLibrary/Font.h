/*
 * File: Font.h
 *
 * Details : Font variable declarations
 *
 */

#ifndef FONT_H_
#define FONT_H_

#include <stdint.h>
#include <stdbool.h>

#define FONT_HEIGHT 5

// array of 2d pixel array image of alphabets
extern const uint8_t *const Alphabet[26];

// width of each letter
extern const uint8_t AlWidth[26];

// array of 2d pixel array of image of digits
extern const uint8_t *const Digits[10];

// width of each digit
extern const uint8_t DiWidth[10];

#endif /* FONT_H_ */
