#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 
#include "Wire.h"

const byte ldrPin = A2;

bool lightState() {
    static bool currentlyOn = true;
    int v = analogRead(ldrPin);
    if (currentlyOn && v > 750) currentlyOn = false;
    else if (!currentlyOn && v < 550) currentlyOn = true;
    return currentlyOn;
}
