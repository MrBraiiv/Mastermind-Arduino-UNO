#include <Arduino.h>
#include "buzzer.h"

static const byte BUZZER_PIN = A3;

static const unsigned int NOTE_C4 = 262;
static const unsigned int NOTE_D4 = 294;
static const unsigned int NOTE_E4 = 330;
static const unsigned int NOTE_G4 = 392;
static const unsigned int NOTE_C5 = 523;
static const unsigned int NOTE_E5 = 659;
static const unsigned int NOTE_G5 = 784;
static const unsigned int NOTE_E6  = 1319;
static const unsigned int NOTE_C6  = 1047;
static const unsigned int NOTE_D6  = 1175;
static const unsigned int NOTE_G6  = 1568;

void clickSound() {
    tone(BUZZER_PIN, 1500, 20);
}

void winSound() {
    tone(BUZZER_PIN, NOTE_E5, 125); delay(130);
    tone(BUZZER_PIN, NOTE_G5, 125); delay(130);
    tone(BUZZER_PIN, NOTE_E6, 125); delay(130);
    tone(BUZZER_PIN, NOTE_C6, 125); delay(130);
    tone(BUZZER_PIN, NOTE_D6, 125); delay(130);
    tone(BUZZER_PIN, NOTE_G6, 250); delay(300);
}

void loseSound() {
    tone(BUZZER_PIN, NOTE_E4, 200);
    delay(220);
    tone(BUZZER_PIN, NOTE_D4, 200);
    delay(220);
    tone(BUZZER_PIN, NOTE_C4, 400);
}
