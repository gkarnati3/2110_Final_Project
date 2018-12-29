//AUTHOR: GARGI PRATYUSHA KARNATI
//CLASS: CS 2110

#include "logic.h"
#include "images/game1.h"
#include "gba.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    //UNUSED(appState);
    appState->gameOver = 0;
    appState->gameOn = 0;
    appState->brickCounter = 5;
    appState->lives = 0;
    appState->points = 0;
    appState->lifelost = 0;
    appState->reset = 0;
    appState->gameWon = 0;

    //init ball
    appState->ball.x = 116;
    appState->ball.y = 120;
    appState->ball.width = 4;
    appState->ball.height = 4;
    appState->ball.color = YELLOW;

    //init paddle
    appState->paddle.x = 120;
    appState->paddle.y = 90;
    appState->paddle.width = 60;
    appState->paddle.height = 4;
    appState->paddle.color = GRAY;
    
    //init bricks
    appState->bricks[0].x = 10;
    appState->bricks[0].y = 10;
    appState->bricks[0].color = RED;
    appState->bricks[1].x = 10;
    appState->bricks[1].y = 55;
    appState->bricks[1].color = BLUE;
    appState->bricks[2].x = 10;
    appState->bricks[2].y = 100;
    appState->bricks[2].color = GREEN;
    appState->bricks[3].x = 10;
    appState->bricks[3].y = 145;
    appState->bricks[3].color = CYAN;
    appState->bricks[4].x = 10;
    appState->bricks[4].y = 190;
    appState->bricks[4].color = MAGENTA;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    UNUSED(keysPressedBefore);

    nextAppState.ball.x = currentAppState->ball.x + 1;
    nextAppState.ball.y = currentAppState->ball.y + 1;
    nextAppState.lives = currentAppState->lives + 1;

    if (keysPressedNow == BUTTON_RIGHT) {
        nextAppState.paddle.y = currentAppState->paddle.y + 1;
    }

    if (keysPressedNow == BUTTON_LEFT) {
        nextAppState.paddle.y = currentAppState->paddle.y - 1;
    }

    return nextAppState;
}
