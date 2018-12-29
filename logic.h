//AUTHOR: GARGI PRATYUSHA KARNATI
//CLASS: CS 2110

#ifndef LOGIC_SEEN
#define LOGIC_SEEN

#include "gba.h"

typedef struct {
    int x;
    int y;
    u16 color;
} Brick;

typedef struct {
    int width;
    int height;
    int x;
    int y;
    u16 color;
} Paddle;

typedef struct {
    int width;
    int height;
    int x;
    int y;
    u16 color;
} Ball;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;

    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */

    int gameOn;
    int gameWon;
    int lifelost;
    int reset;
    int brickCounter;
    int lives;
    int points;
    Brick bricks[5];
    Ball ball;
    Paddle paddle;
    // Brick bricks[5];
    // Paddle paddleToMove;
    // Ball ballMoved;

} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
