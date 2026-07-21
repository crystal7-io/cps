#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!IMU.begin()) while (1);
}

void loop() {
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    Serial.print("X:"); Serial.print(x); Serial.print("\t");
    Serial.print("Y:"); Serial.print(y); Serial.print("\t");
    Serial.print("Z:"); Serial.println(z);
  }
}