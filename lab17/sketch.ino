#include <Arduino_APDS9960.h>

int greenPin = 3;
int count = 0;
bool wasFar = true;

void setup() {
  Serial.begin(9600);
  APDS.begin();
  pinMode(greenPin, OUTPUT);
}

void loop() {
  if (APDS.proximityAvailable()) {
    int prox = APDS.readProximity();
    bool isNear = prox >= 100;

    if (isNear && wasFar) {
      count = count + 1;
      Serial.println(count);
    }
    wasFar = !isNear;

    if (count >= 15) {
      digitalWrite(greenPin, HIGH);
    }
  }
}
