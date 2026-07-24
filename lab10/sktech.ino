#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setRGB(0, 128, 255);
  lcd.setCursor(0, 0);
  lcd.print("Grove LCD Ready");
  lcd.setCursor(0, 1);
  lcd.print("Nano 33 BLE");
}

void loop() {
}
