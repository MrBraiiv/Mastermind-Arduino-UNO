#include <Arduino.h>
#include "headers.h"

const byte redPin = 3, greenPin = 5, bluePin = 6;

void setupPins() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

static void setColor(byte r, byte g, byte b) {
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
}

unsigned long lastBlink = 0;
bool blinkState = true;
static void blinkLed() {
    if (millis() - lastBlink >= 150) {
        lastBlink = millis();
        blinkState = !(blinkState);
        if (blinkState) setColor(255, 0, 0); else setColor(0, 0, 0);
    }
}

void handleRGB(GameState *gs) {
    if (gs->state == WIN)
        setColor(0, 0, 255);
    else if (gs->state == LOSE) {
        setColor(0, 0, 0);
        return;
    }

    switch (gs->turn) {
        case 1:
            setColor(0, 255, 0);
            break;
        case 2:
            setColor(120, 255, 0);
            break;
        case 3:
            setColor(180, 255, 0);
            break;
        case 4:
            setColor(255, 255, 0);
            break;
        case 5:
            setColor(255, 180, 0);
            break;
        case 6:
            setColor(255, 100, 0);
            break;
        case 7:
            setColor(255, 0, 0);
            break;
        case 8:
            setColor(139, 0, 0);
            break;
        default:
            break;
    }
}

void rgbTick(GameState *gs) {
    if (gs->count == 1) blinkLed();
}
