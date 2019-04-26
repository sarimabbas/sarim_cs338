#include "driver.hpp"
#include <Arduino.h>
#include <string.h>

Servo frontBackServo, upDownServo, gripperServo, baseServo;
long frontBackPos, upDownPos, gripperPos, basePos;

int driverSetup(int frontBackPin, int upDownPin, int gripperPin, int basePin) {
    // attach to pins
    frontBackServo.attach(frontBackPin);
    upDownServo.attach(upDownPin);
    gripperServo.attach(gripperPin);
    baseServo.attach(basePin);
    // initialize position variables
    frontBackPos = NEUTRAL_POS;
    upDownPos = NEUTRAL_POS;
    gripperPos = NEUTRAL_POS;
    basePos = NEUTRAL_POS;
    // set to neutral position
    frontBackServo.write(frontBackPos);
    upDownServo.write(upDownPos);
    gripperServo.write(gripperPos);
    baseServo.write(basePos);
    return 0;
}

int manipulateServo(const char* servo, int pos) {
    // only update if within bounds
    if (!(pos >= MIN_POS && pos <= MAX_POS)) {
        return -1;
    }
    // only update if != prev position
    if (strcmp("FB", servo) == 0) {
        if (pos != frontBackPos) {
            frontBackPos = pos;
            frontBackServo.write(frontBackPos);
        }
    } else if (strcmp("UP", servo) == 0) {
        if (pos != upDownPos) {
            upDownPos = pos;
            upDownServo.write(upDownPos);
        }
    } else if (strcmp("GR", servo) == 0) {
        if (pos != gripperPos) {
            gripperPos = pos;
            gripperServo.write(gripperPos);
        }
    } else if (strcmp("BS", servo) == 0) {
        if (pos != basePos) {
            basePos = pos;
            baseServo.write(basePos);
        }
    } else {
        // invalid servo
        return -1;
    }
    return 0;
}

int gripperClose(void) {
    for (int pos = MIN_POS; pos <= MAX_POS; pos += 1) {
        manipulateServo("GR", pos);
        delay(15);
    }
}

int gripperOpen(void) {
    for (int pos = MAX_POS; pos >= MIN_POS; pos -= 1) {
        manipulateServo("GR", pos);
        delay(15);
    }
}
