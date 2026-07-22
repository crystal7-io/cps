#include <ArduinoBLE.h>

BLEService ledService("180A");
BLECharCharacteristic ledChar("2A57", BLERead | BLEWrite);
int redPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  BLE.begin();
  BLE.setLocalName("MyBoard");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(ledChar);
  BLE.addService(ledService);
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    while (central.connected()) {
      if (ledChar.written()) {
        char value = ledChar.value();
        if (value == 'A') {
          digitalWrite(redPin, HIGH);
        } else if (value == 'B') {
          digitalWrite(redPin, LOW);
        }
      }
    }
  }
}
