int inputPin = A0;
int outputPin = 11;

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
}

void loop() {
    int reading = analogRead(inputPin);
    int mappedReading = map(reading, 0, 1023, 0, 255);
    Serial.println(mappedReading);
    analogWrite(outputPin, mappedReading);
    delay(1000);
}
