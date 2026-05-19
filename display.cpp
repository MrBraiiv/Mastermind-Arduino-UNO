#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "headers.h"
#include "display.h"
#include "ldr.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static void updateFeedback(char *row0, char *code, byte exact, byte misp);
static void showHints(char *row1);
static void displayScreen(char *row0, char *row1);
static void cursorAnimation();

void displayInit() {
    Wire.begin();
    lcd.init();
}

void displaySetBacklight() {
    if (lightState()) lcd.backlight();
    else lcd.noBacklight();
}

void render(GameState *gs) {
    char row0[17] = "----|E:- M:-|C:-",
         row1[17] = "                ";
    byte line = gs->historyLine;
    row0[15] = gs->count + '0';

    if (gs->state == PLAY) {
        strncpy(row1, gs->guessCode, 4);
        if (gs->turn > 1) {
            updateFeedback(row0, gs->historyCode[line], gs->historyExact[line], gs->historyMisp[line]);
            showHints(row1);
        }

    } else if (gs->state == HISTORY) {
        row0[13] = 'T';
        row0[15] = gs->historyLine + 1 + '0';
        strncpy(row1, gs->guessCode, 4);
        if (gs->turn > 1) {
            updateFeedback(row0, gs->historyCode[line], gs->historyExact[line], gs->historyMisp[line]);
            showHints(row1);
        }

    } else if (gs->state == WIN) {
        snprintf(row1, 17, "YOU WIN!  S9=new");
        updateFeedback(row0, gs->historyCode[line], gs->historyExact[line], gs->historyMisp[line]);

    } else if (gs->state == LOSE) {
        row0[0] = row0[1] = row0[2] = row0[3] = '?';
        snprintf(row1, 17, "LOST. Code:%s ", gs->secretCode);
    }

    displayScreen(row0, row1);
    lcd.setCursor(gs->curs, 1);
}

static void updateFeedback(char *row0, char *code, byte exact, byte misp) {
    strncpy(row0, code, 4);
    row0[7] = exact + '0';
    row0[11] = misp + '0';
}

static void showHints(char *row1) {
    row1[13] = '^';
    row1[14] = 'v';
    row1[15] = 'X';
}

static void displayScreen(char *row0, char *row1) {
    lcd.setCursor(0,0);
    lcd.print(row0);
    lcd.setCursor(0,1);
    lcd.print(row1);
}

void cursorDisplay(Mode state) {
    if (state == PLAY) lcd.blink();
    else lcd.noBlink();
}

static unsigned long last_blink = 0;
static bool swap = true;
