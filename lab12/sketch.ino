#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  APDS.begin();
}

void loop() {
  if (APDS.gestureAvailable()) {
    int dir = APDS.readGesture();
    if (dir == GESTURE_UP) {
      Serial.println("UP");
    } else if (dir == GESTURE_DOWN) {
      Serial.println("DOWN");
    } else if (dir == GESTURE_LEFT) {
      Serial.println("LEFT");
    } else if (dir == GESTURE_RIGHT) {
      Serial.println("RIGHT");
    }
  }
}
