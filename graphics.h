//AUTHOR: GARGI PRATYUSHA KARNATI
//CLASS: CS 2110

#ifndef GRAPHICS_SEEN
#define GRAPHICS_SEEN

#include "logic.h"
#include "gba.h"
#define DRAW_RED_BRICK(r, c, color) drawRectDMA(r, c, 40, 10, color);
#define DRAW_BLUE_BRICK(r, c, color) drawRectDMA(r, c, 40, 10, color);
#define DRAW_GREEN_BRICK(r, c, color) drawRectDMA(r, c, 40, 10, color);
#define DRAW_CYAN_BRICK(r, c, color) drawRectDMA(r, c, 40, 10, color);
#define DRAW_MAGENTA_BRICK(r, c, color) drawRectDMA(r, c, 40, 10, color);

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state, int reset);

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state, u32 button);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state, u32 button);

// If you have anything else you need accessible from outside the graphics.c
// file, you can add them here. You likely won't.

void undrawBall(int ballx, int bally);

void drawBall(int ballx, int bally);

void move(int ballx, int bally);

void gameActions(AppState *state);

#endif
