#include <Arduino_APDS9960.h>

int redPin = 2;
int greenPin = 3;
int bluePin = 4;

void setup() {
  Serial.begin(9600);
  APDS.begin();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if (APDS.proximityAvailable()) {
    int prox = APDS.readProximity();
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);

    if (prox > 200) {
      digitalWrite(bluePin, HIGH);
    } else if (prox >= 100 && prox <= 200) {
      digitalWrite(greenPin, HIGH);
    } else if (prox < 100) {
      digitalWrite(redPin, HIGH);
    }
  }
}
