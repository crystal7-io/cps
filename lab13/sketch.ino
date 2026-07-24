#include <Arduino_APDS9960.h>

void setLed(bool redOn, bool greenOn, bool blueOn) {
  // Nano 33 BLE Sense RGB LED channels are active LOW.
  digitalWrite(LEDR, !redOn);
  digitalWrite(LEDG, !greenOn);
  digitalWrite(LEDB, !blueOn);
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  setLed(false, false, false);

  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960.");
    while (true) {}
  }
}

void loop() {
  if (!APDS.proximityAvailable()) return;

  int proximity = APDS.readProximity();
  Serial.print("Proximity: ");
  Serial.println(proximity);

  if (proximity < 100) {
    setLed(true, false, false);       // Red
  } else if (proximity < 200) {
    setLed(false, true, false);       // Green
  } else {
    setLed(false, false, true);       // Blue
  }
  delay(200);
}
