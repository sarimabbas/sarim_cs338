

int ledOne = 6;
int ledTwo = 7;

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(ledOne, OUTPUT);
    pinMode(ledTwo, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(ledOne, HIGH);
    digitalWrite(ledTwo, HIGH);
    delay(1000);       
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    delay(1000);   
}
