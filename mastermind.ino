#include "headers.h"
#include "display.h"
#include "input.h"
#include "game.h"
#include "rgbLed.h"

GameState gs;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(A0));
    displayInit();
    gameInit(&gs);
    render(&gs);
}
void loop() {
    if(inputPoll(&gs)) render(&gs);
    cursorDisplay(gs.state);
    rgbTick(&gs);
}
