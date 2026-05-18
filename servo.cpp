#include <Arduino.h>
#include "servo.h"
#include <Servo.h>
const Servo servo;

void setupServo() {
    servo.attach(11, 544, 2400);   
    servo.write(0);
}
   
byte flagAngle = 0;
unsigned long previousMillis = 0;    
void winFlag() {
        while (flagAngle < 90) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= 3) {  
                previousMillis = currentMillis;
                flagAngle++;
                servo.write(flagAngle);
            }

        }
        servo.write(90);
        flagAngle = 90;
    
         unsigned long waitStart = millis();
         while (millis() - waitStart < 5000) {}


        previousMillis = millis();      
        while (flagAngle > 0) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= 20) {
                previousMillis = currentMillis;
                flagAngle--;
                servo.write(flagAngle);
            }
        }
        servo.write(0);
        flagAngle = 0;
     }

