/*
 * File: RenderWorld.h
 *
 * Details : Defines and renders the game world layout, comprising
 * obstacles, coins, roads, and sidewalks. It set, configures, shifts
 * and displays the game world on LT24.
 *
 * Author: Santosh K S
 *
 */

// Include guards to prevent multiple header inclusions
#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

// Header inclusion
// Standard C library
#include <stdint.h> // C bool Library
#include <stdbool.h> // C header for integer types with specific widths

#include "Sprites.h" // Sprite dimensions and definitions

#include "DE1SoC_LT24/DE1SoC_LT24.h" // Driver for the LT24 Display Controller

//
// Function: LT24_copyGrayFrameBuffer
// Details: Copy frame buffer to display after converting it to grayscale image.
// Arguments: Driver context, frame buffer address, starting position, frame dimensions
// Return: 0 if successful
//
HpsErr_t LT24_copyGrayFrameBuffer( PLT24Ctx_t ctx, const unsigned short* framebuffer, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height );

//
// Function: LT24_drawColourWindow
// Details: Function colour a part of the display with
// with single colour value.
// Arguments: Driver context, RGB565 colour value, starting position, frame dimensions
// Return: true if successful
//
HpsErr_t LT24_drawColourWindow( PLT24Ctx_t ctx, unsigned short Colour, unsigned int xleft, unsigned int ytop, unsigned int width, unsigned int height );

//
// Function: GetRandomNumber
// Details: Generates 16 bit random number using Linear-Feedback Shift Register
// Arguments: Void.
// Return: 16 bit unsigned random number
//
uint16_t GetRandomNumber();

//
// Function: SetWorldBlock
// Details: Creates game world blocks to be rendered
// from the random number.
// Arguments: Worldblock structure
// Return: Void. Configures the world block sent in the argument.
//
void SetWorldBlock(WorldBlock *Block);

//
// Function: RenderWorldBlock
// Details: Renders the game world blocks on LT24 display
// Arguments: world block address, LT24 driver context
// Return: Void.
//
void RenderWorldBlock(WorldBlock *Block, PLT24Ctx_t ctx);

//
// Function: ShiftWorldBlock
// Details: Shifts the block position related parameters by
// given shift value vertically. This gives a perception that
// car is moving forward when infact the game world is moving back.
// Arguments: Worldblock array, vertical shift value
// Return: Void. Updates the world block positional parameters in the WBlock argument.
//
void ShiftWorldBlock(WorldBlock WBlocks[], uint8_t ShiftY);

//
// Function: RenderWorld
// Details: Renders the world consisting of six world blocks on the LT24 display.
// Arguments: World block array, LT24 driver context, vertical shift value
// Return: Void.
//
void RenderWorld(WorldBlock *Block, PLT24Ctx_t ctx, uint8_t ShiftY);

//
// Function: InitWorldBlock
// Details: Sets the initial game world configuration. The game
// will always start with this configuration of blocks, obstacles and coins.
// Arguments: World block array.
// Return: Void.
//
void InitWorldBlock(WorldBlock WBlocks[]);

//
// Function: RenderGrayScreen
// Details: Displays the world blocks in grayscale colour format.
// Arguments: World block array, Lt24 display driver context
// Return: Void.
//
void RenderGrayScreen(WorldBlock WBlocks[], PLT24Ctx_t lt24);

#endif /* RENDERWORLD_H_ */
