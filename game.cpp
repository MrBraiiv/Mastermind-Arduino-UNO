#include <string.h>
#include <Arduino.h>
#include "headers.h"
#include "game.h"
#include "rgbLed.h"
#include "sound.h"
#include "servo.h"

static byte symbolIndex(char c) { // to be used as indexing for code chars
    return c - 'A';
}


static char randomChar() {
    return random(6) + 'A';
}

static void setRandomCode(char *secret) {
    for (byte i = 0; i < 4; i++) secret[i] = randomChar();
}

static byte totalMatches(char *secret, char *guess) {
    byte secretCounts[6] = {0}, guessCounts[6] = {0};

    for (byte i = 0; i < 4; i++) {
        secretCounts[symbolIndex(secret[i])]++;
        guessCounts[symbolIndex(guess[i])]++;
    }

    byte total = 0;
    for (byte i = 0; i < 6; i++)
        total += min(secretCounts[i], guessCounts[i]);
    return total;
}

static byte calcExact(char *secret,char *guess) {
    byte rightplace = 0;

    for(byte i = 0; i < 4 ; i++){
            if(guess[i] == secret[i]) rightplace++;
    }

    return rightplace;
}

static byte calcMisp(char *secret, char *guess) {
    return totalMatches(secret, guess) - calcExact(secret, guess);
}

void gameSubmitGuess(GameState *gs) {
    byte exacts = calcExact(gs->secretCode, gs->guessCode);
    byte misp = calcMisp(gs->secretCode, gs->guessCode);

    if (gs->turn > 1) gs->historyLine++;
    byte hl = gs->historyLine;
    for (byte i = 0; i < 4; i++) gs->historyCode[hl][i] = gs->guessCode[i];
    gs->historyExact[hl] = exacts;
    gs->historyMisp[hl] = misp;
    gs->turn++;
    gs->count--;
    for (byte i = 0; i < 4; i++) gs->guessCode[i] = ' ';
    gs->curs = 0;

    if (exacts == 4) {
        gs->state = WIN;
        winSound();
        winFlag();
    } else if (gs->count == 0) {
        gs->state = LOSE;
        loseSound();
    }
    handleRGB(gs);
}

void gameInit(GameState *gs) {
    for (byte i = 0; i < 4; i++) gs->guessCode[i] = ' ';
    gs->guessCode[4] = '\0';
    setRandomCode(gs->secretCode); 
    gs->turn = 1;
    gs->count = 9;
    gs->curs = 0;
    gs->state = PLAY;
    gs->historyLine = 0;
    handleRGB(gs);
}

void setupInit() {
    setupServo();
    setupPins();
}
