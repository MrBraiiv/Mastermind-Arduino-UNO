#include <Arduino.h>
#include "sound.h"

static const byte BUZZER_PIN = A3;
static const byte POT_PIN = A1;

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

unsigned int getFrequency() {
    int raw = analogRead(POT_PIN);
    if (raw < 10) return 0;
    return map(raw, 10, 1023, 200, 2000);
}

static void safeTone(int freq, unsigned int duration) {
    if (freq < 100) freq = 100;
    tone(BUZZER_PIN, (unsigned int)freq, duration);
}

void clickSound() {
    unsigned int freq = getFrequency();
    if (freq == 0) return;

    tone(BUZZER_PIN, freq, 20);
}

void winSound() {
    unsigned int freq = getFrequency();
    if (freq == 0) return;

    int offset = (int)freq - 1100;

    safeTone(NOTE_E5 + offset, 125); delay(130);
    safeTone(NOTE_G5 + offset, 125); delay(130);
    safeTone(NOTE_E6 + offset, 125); delay(130);
    safeTone(NOTE_C6 + offset, 125); delay(130);
    safeTone(NOTE_D6 + offset, 125); delay(130);
    safeTone(NOTE_G6 + offset, 250); delay(300);
}

void loseSound() {
    unsigned int freq = getFrequency();
    if (freq == 0) return;

    int offset = (int)freq - 1100;

    safeTone(NOTE_E4 + offset, 200); delay(220);
    safeTone(NOTE_D4 + offset, 200); delay(220);
    safeTone(NOTE_C4 + offset, 400);
}
