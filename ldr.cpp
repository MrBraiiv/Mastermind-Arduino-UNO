#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 
#include "Wire.h"

const byte ldrPin = A2;
const int range = 650;
extern LiquidCrystal_I2C lcd;

bool lightState() {
    return analogRead(ldrPin) < range;
}
