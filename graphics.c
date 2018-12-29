//AUTHOR: GARGI PRATYUSHA KARNATI
//CLASS: CS 2110

#include "graphics.h"
#include "gba.h"
// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
#include "images/garbage.h"
#include "images/title.h"
#include "images/game1.h"
#include "stdio.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);

// This function will be used to draw everything about the app
// including the background and whatnot.

int padx, pady, padw, padh, padc;
int volatile ballx, bally, ballw, ballh, ballc;
int ballrow, ballcol = 1;
int score = 0;
char scoreWriter[sizeof(unsigned int) * 3 + 2];
char livesWriter[sizeof(unsigned int) * 3 + 2];
int brickHit = 0;
int lives = 0;
int colored[5] = {0, 0, 0, 0, 0};

void fullDrawAppState(AppState *state, int reset) {
    // TA-TODO: IMPLEMENT.
    if (reset == 1) {
        lives = state->lives;
        score = state->points;
        for (int i = 0; i < 5; i++) {
            colored[i] = 0;
        }
    }
    fillScreenDMA(BLACK);
    brickHit = state->brickCounter;
    padx = state->paddle.x;
    pady = state->paddle.y;
    padw = state->paddle.width;
    padh = state->paddle.height;
    padc = state->paddle.color;
    drawRectDMA(padx, pady, padw, padh, padc);
    ballx = state->ball.x;
    bally = state->ball.y;
    ballw = state->ball.width;
    ballh = state->ball.height;
    ballc = state->ball.color;
    drawRectDMA(ballx, bally, ballw, ballh, ballc);
    DRAW_RED_BRICK(state->bricks[0].x, state->bricks[0].y, state->bricks[0].color);
    DRAW_BLUE_BRICK(state->bricks[1].x, state->bricks[1].y, state->bricks[1].color);
    DRAW_GREEN_BRICK(state->bricks[2].x, state->bricks[2].y, state->bricks[2].color);
    DRAW_CYAN_BRICK(state->bricks[3].x, state->bricks[3].y, state->bricks[3].color);
    DRAW_MAGENTA_BRICK(state->bricks[4].x, state->bricks[4].y, state->bricks[4].color);
    if (reset == 0) {
        for (int i = 0; i < 5; i++) {
            if (colored[i] == 1) {
                drawRectDMA(10, state->bricks[i].y, 40, 10, BLACK);
            }
        }
    }
    
    // char scoreWriter[sizeof(unsigned int) * 3 + 2];
    sprintf(scoreWriter, "Score: %d", score);
    drawString(10, 145, scoreWriter, WHITE);
    
    // char livesWriter[sizeof(unsigned int) * 3 + 2];
    sprintf(livesWriter, "Lives Lost: %d", lives);
    drawString(150, 145, livesWriter, WHITE);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state, u32 button) {
    // TA-TODO: IMPLEMENT.
    UNUSED(state);
    if (button == BUTTON_RIGHT && pady < 180) { //right
        drawRectDMA(120, pady, 1, padh, BLACK);
    }
    if (button == BUTTON_LEFT && pady > 0) { //left
        drawRectDMA(120, pady + padw - 1, 1, padh, BLACK);
    }
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state, u32 button) {
    // TA-TODO: IMPLEMENT.
    UNUSED(state);
    if (button == BUTTON_RIGHT && pady < 180) { //right
        pady++;
        drawRectDMA(120, pady, padw, padh, padc);
    }
    if (button == BUTTON_LEFT && pady > 0) { //left
        pady--;
        drawRectDMA(120, pady, padw, padh, padc);
    }
}

void undrawBall(int ballx, int bally) {
    drawRectDMA(ballx, bally, ballw, ballh, BLACK);
}

void drawBall(int ballx, int bally) {
    drawRectDMA(ballx, bally, ballw, ballh, ballc);
}

void gameActions(AppState *state) {
    if (score == 100 || brickHit == 0) {
        state->gameWon = 1;
    }

    //check paddle left
    if (((ballx + 4) == padx) && (bally >= pady)) {
        if (bally <= (pady + 20)) {
            undrawBall(ballx, bally);
            ballrow = -1; 
            ballcol = -1;
        }
    }

    //check paddle middle
    if (((ballx + 4) == padx) && (bally >= pady)) {
        if ((bally >= (pady + 20)) && (bally <= (pady + 40))) {
            undrawBall(ballx, bally);
            ballrow = -1; 
            ballcol = 0; 
        }
    }

    //check paddle right
    if (((ballx + 4) == padx) && (bally >= pady)) {
        if ((bally >= (pady + 40)) && (bally <= (pady + 60))) {
            undrawBall(ballx, bally);
            ballrow = -1; 
            ballcol = 1;
        }
    }
    
    //hits walls
    if (ballx > 150) { //row down
        if (lives > 2) {
            state->gameOver = 1;
        } else {
            undrawBall(ballx, bally);
            ballx = 150 - 4 + 1;
            ballrow = -ballrow;
            lives++;
            state->lifelost = 1;
            sprintf(livesWriter, "Lives Lost: %d", lives);
            drawString(150, 145, livesWriter, WHITE);
        }
    }

    if (ballx == 0) { //row up
        undrawBall(ballx, bally);
        ballx = 10 + 4;
        ballrow = -ballrow;
    }

    if (bally == 0) { //left col
        undrawBall(ballx, bally);
        bally = 0;
        ballcol = -ballcol;
    }

    if (bally == 240) { //right col
        undrawBall(ballx, bally);
        bally = 240 - 4 + 1;
        ballcol = -ballcol;
    }

    for (int i = 0; i < 5; i++) {
         // Check bottom side of a block
        if ((colored[i] == 0) && ballx == state->bricks[i].x + 10 && (bally + 4 >= state->bricks[i].y && bally <= state->bricks[i].y + 40)) {
            undrawBall(ballx, bally);
            drawBall(ballx++, bally);

            score += 20;
            sprintf(scoreWriter, "Score: %d", score);
            drawRectDMA(145, 10, 50, 10, BLACK);
            drawString(10, 145, scoreWriter, WHITE);

            brickHit--;

            drawRectDMA(state->bricks[i].x, state->bricks[i].y, 40, 10, BLACK);
            colored[i] = 1;

            state->bricks[i].y = -100;
            state->bricks[i].x = -100;
        } else if ((colored[i] == 0) && ballx + 4 == state->bricks[i].x && (bally + 4 >= state->bricks[i].y && bally <= state->bricks[i].y + 40)) { // Check top side of a block
            undrawBall(ballx, bally);
            drawBall(ballx++, bally);

            score += 20;
            sprintf(scoreWriter, "Score %d:", score);
            drawRectDMA(145, 10, 50, 10, BLACK);
            drawString(10, 145, scoreWriter, WHITE);

            brickHit--;

            drawRectDMA(state->bricks[i].x, state->bricks[i].y, 40, 10, BLACK);
            colored[i] = 1;

            state->bricks[i].y = -100;
            state->bricks[i].x = -100;
        } else if ((colored[i] == 0) && ballx >= state->bricks[i].x && (ballx <= state->bricks[i].x + 10 && bally + 4 == state->bricks[i].y)) { // Check left side of a block
            undrawBall(ballx, bally);
            drawBall(ballx, bally++);

            score += 20;
            sprintf(scoreWriter, "Score %d:", score);
            drawRectDMA(145, 10, 50, 10, BLACK);
            drawString(10, 145, scoreWriter, WHITE);

            brickHit--;

            drawRectDMA(state->bricks[i].x, state->bricks[i].y, 40, 10, BLACK);
            colored[i] = 1;

            state->bricks[i].y = -100;
            state->bricks[i].x = -100;
        } else if ((colored[i] == 0) && ballx >= state->bricks[i].x && (ballx <= state->bricks[i].x + 10 && bally == state->bricks[i].y + 40)) { // Check right side of a block
            undrawBall(ballx, bally);
            drawBall(ballx, bally--);

            score += 20;
            sprintf(scoreWriter, "Score %d:", score);
            drawRectDMA(145, 10, 50, 10, BLACK);
            drawString(10, 145, scoreWriter, WHITE);

            brickHit--;

            drawRectDMA(state->bricks[i].x, state->bricks[i].y, 40, 10, BLACK);
            colored[i] = 1;

            state->bricks[i].y = -100;
            state->bricks[i].x = -100;
        }
    }
    undrawBall(ballx, bally);
    ballx = ballx + ballrow;
    bally = bally + ballcol;
    drawBall(ballx, bally);
}


