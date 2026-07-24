#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960!");
    while (1);
  }
  Serial.println("Gesture Sensor Ready");
}

void loop() {
  if (APDS.gestureAvailable()) {
    switch (APDS.readGesture()) {
      case GESTURE_LEFT: Serial.println("LEFT"); break;
      case GESTURE_RIGHT: Serial.println("RIGHT"); break;
      case GESTURE_UP: Serial.println("UP"); break;
      case GESTURE_DOWN: Serial.println("DOWN"); break;
    }
  }
}
