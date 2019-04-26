#include "driver.hpp"

void setup() {
    Serial.begin(9600);

    // initialize servos
    driverSetup(10, 11, 12, 13);

    gripperOpen();
    delay(1000);
    moveLeft();
    delay(1000);
    moveDown();
    delay(1000);
    gripperClose();
    delay(1000);
    moveUp();
    delay(1000);
    moveRight();
    delay(1000);
    moveDown();
    delay(1000);
    gripperOpen();
    delay(1000);
    moveUp();
    delay(1000);
}

void loop() {

}
