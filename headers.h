#ifndef HEADERS_H
#define HEADERS_H

#include <Arduino.h>

typedef enum {PLAY, HISTORY, WIN, LOSE} Mode;

typedef struct {
    char guessCode[5],
         secretCode[5],
         historyCode[9][4];
    byte historyExact[9],
         historyMisp[9],
         historyLine,
         count,
         turn,
         curs; //cursor
    Mode state;
} GameState;

#endif
