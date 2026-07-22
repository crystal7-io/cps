#include <ArduinoBLE.h>

BLEService sensorService("180A");
BLEUnsignedIntCharacteristic sensorChar("2A58", BLERead | BLENotify);

void setup() {
  Serial.begin(9600);
  BLE.begin();
  BLE.setLocalName("MyBoard");
  BLE.setAdvertisedService(sensorService);
  sensorService.addCharacteristic(sensorChar);
  BLE.addService(sensorService);
  sensorChar.writeValue(0);
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    while (central.connected()) {
      int sensorValue = analogRead(A0);
      sensorChar.writeValue(sensorValue);
    }
  }
}
