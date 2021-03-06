//AUTHOR: GARGI PRATYUSHA KARNATI
//CLASS: CS 2110

#include "gba.h"
#include "logic.h"
#include "graphics.h"
#include "images/title2.h"
#include "images/game1.h"
#include "images/game2.h"
#include "images/sad.h"
#include "images/tryagain.h"
// TA-TODO: Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
//#include "images/garbage.h"

#include <stdio.h>
#include <stdlib.h>

// AppState enum definition
typedef enum {
    // TA-TODO: Add any additional states you need for your app.
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_LOST_LIFE,
    APP_WIN,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

int main(void) {
    // TA-TODO: Manipulate REG_DISPCNT here to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;
    int reset = nextAppState.reset;

    while(1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // TA-TODO: Manipulate the state machine below as needed.
        switch(state) {
        case START:
            // Wait for VBlank
            waitForVBlank();

            // TA-TODO: Draw the start state here.
            drawFullScreenImageDMA((short unsigned int*) (title2));
            state = START_NODRAW;
            break;
        case START_NODRAW:
            // TA-TODO: Check for a button press here to start the app.
            // Start the app by switching the state to APP_INIT.
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                state = APP_INIT;
            }
            break;
        case APP_INIT:
            // Initialize the app. Switch to the APP state.
            initializeAppState(&currentAppState);

            // Draw the initial state of the app
            fullDrawAppState(&currentAppState, reset);

            if (reset == 1) {
                nextAppState.reset = 0;
                reset = nextAppState.reset;
            }

            state = APP;
            break;
        case APP:
            if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                nextAppState.reset = 1;
                reset = nextAppState.reset;
                state = START;
            }

            // Process the app for one frame, store the next state
            nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

            // Wait for VBlank before we do any drawing.
            waitForVBlank();

            gameActions(&nextAppState);
            
            if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
                undrawAppState(&currentAppState, BUTTON_RIGHT);
                drawAppState(&nextAppState, BUTTON_RIGHT);
            }

            if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
                undrawAppState(&currentAppState, BUTTON_LEFT);
                drawAppState(&nextAppState, BUTTON_LEFT);  
            }

            // Check if the app is exiting. If it is, then go to an exit state.
            if (nextAppState.lifelost) state = APP_LOST_LIFE;
            if (nextAppState.gameOver) state = APP_EXIT;
            if (nextAppState.gameWon) state = APP_WIN;

            currentAppState = nextAppState;

            break;
        case APP_LOST_LIFE:
            // Wait for VBlank
            waitForVBlank();

            if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                nextAppState.reset = 1;
                reset = nextAppState.reset;
                state = START;
            }

            // TA-TODO: Draw the mid-exit / game almost over screen
            fillScreenDMA(MAGENTA);
            drawString(70, 30, "You Lost a LIFE!", BLACK);
            drawImageDMA(60, 100, 50, 37, (short unsigned int*) (sad));
            nextAppState.lifelost = 0;

            for (int i = 0; i < 300; i++) {
                waitForVBlank();
            }

            state = APP_INIT;
            break;
        case APP_WIN:
            // Wait for VBlank
            waitForVBlank();

            // TA-TODO: Draw the exit / gamewin screen
            
            drawFullScreenImageDMA((short unsigned int*) (tryagain));
            drawString(70, 30, "YOU WON! Be happy.", BLACK);

            state = APP_EXIT_NODRAW;
            break;
        case APP_EXIT:
            // Wait for VBlank
            waitForVBlank();

            // TA-TODO: Draw the exit / gameover screen

            drawFullScreenImageDMA((short unsigned int*) (game2));
            drawString(100, 140, "You Lost!", WHITE);

            state = APP_EXIT_NODRAW;
            break;
        case APP_EXIT_NODRAW:
            // TA-TODO: Check for a button press here to go back to the start screen
            if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                nextAppState.reset = 1;
                reset = nextAppState.reset;
                state = START;
            }
            break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
