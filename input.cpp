#include <Arduino.h>
#include <Keypad.h>
#include "headers.h"
#include "input.h"
#include "game.h"
#include "sound.h"

void debugDumpState(GameState *gs) {
    Serial.println(F("--- GameState ---"));
    Serial.print(F("state       = ")); Serial.println(gs->state);
    Serial.print(F("turn        = ")); Serial.println(gs->turn);
    Serial.print(F("count       = ")); Serial.println(gs->count);
    Serial.print(F("curs        = ")); Serial.println(gs->curs);
    Serial.print(F("historyLine = ")); Serial.println(gs->historyLine);
    Serial.print(F("guessCode   = [")); Serial.print(gs->guessCode); Serial.println(F("]"));
    Serial.print(F("secretCode  = [")); Serial.print(gs->secretCode); Serial.println(F("]"));
    Serial.println(F("history:"));
    for (byte t = 0; t < gs->turn; t++) {
        Serial.print(F("  ["));
        Serial.print(t); Serial.print(F("] "));
        for (byte i = 0; i < 4; i++) Serial.print(gs->historyCode[t][i]);
        Serial.print(F("  E=")); Serial.print(gs->historyExact[t]);
        Serial.print(F(" M=")); Serial.println(gs->historyMisp[t]);
    }
    Serial.println();
}


static const byte ROWS = 3;
static const byte COLS = 4;

static char keymap[ROWS][COLS] = {
    { 'A', 'B', 'C', 'D' },
    { 'E', 'F', 'U', 'V' }, // U = Up, V = Down
    { 'K', 'X', 'L', 'R' }, // K = OK, X = Exit, L = Left, R = Right
};

static byte rowPins[ROWS] = { 12, 10, 9};
static byte colPins[COLS] = { 8, 7, 4, 2 };

static Keypad kpad = Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);

static bool guessComplete(GameState *gs) {
    for (byte i = 0; i < 4; i++) {
        if (gs->guessCode[i] == ' ') return false;
    }
    return true;
}

static bool historyAvailable(GameState *gs) {
    return gs->turn > 2;
}

static void handleSymbolKey(GameState *gs, char sym) {
    if (gs->state != PLAY) return;
    gs->guessCode[gs->curs] = sym;
    if (gs->curs < 3) gs->curs++;
}

static void handleSubmit(GameState *gs) {
    if (gs->state == PLAY && guessComplete(gs)) gameSubmitGuess(gs); // [game.cpp]
    else if (gs->state == WIN || gs->state == LOSE) gameInit(gs); // [mastermind.ino]                      
}


static void handleLeft(GameState *gs) {
    if (gs->state != PLAY) return;
    if (gs->curs > 0) gs->curs--;
}

static void handleRight(GameState *gs) {
    if (gs->state != PLAY) return;
    if (gs->curs < 3) gs->curs++;
}

static void handleScrollUp(GameState *gs) {
    if (gs->state == PLAY && historyAvailable(gs)) {
        gs->state = HISTORY;
        gs->historyLine = gs->turn - 3;
    } else if (gs->state == HISTORY) {
        if (gs->historyLine > 0) gs->historyLine--;
    }
}

static void handleScrollDown(GameState *gs) {
    if (gs->state == HISTORY) {
        if (gs->historyLine < gs->turn - 3) gs->historyLine++;
        else { gs->historyLine = gs->turn - 2; gs->state = PLAY; }
    }
}

static void handleExitHistory(GameState *gs) {
    if (gs->state == HISTORY) {
        gs->historyLine = gs->turn - 2;
        gs->state = PLAY;
    }
}


bool inputPoll(GameState *gs) {
    char key = kpad.getKey();
    if (!key) return 0;
    clickSound();

    switch (key) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F': handleSymbolKey(gs, key); break;

        case 'K': handleSubmit(gs);       break;
        case 'L': handleLeft(gs);         break;
        case 'R': handleRight(gs);        break;
        case 'U': handleScrollUp(gs);     break;
        case 'V': handleScrollDown(gs);   break;
        case 'X': handleExitHistory(gs);  break;

        default: break;
    }
    // TODO: delete after test
    debugDumpState(gs);
    return 1;

}

