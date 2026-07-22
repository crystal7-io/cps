#include <mbed.h>

rtos::Thread blinkThread;
rtos::Thread printThread;
int ledPin = 2;

void blinkTask() {
  while (true) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    rtos::ThisThread::sleep_for(500);
  }
}

void printTask() {
  while (true) {
    Serial.println("hello from thread");
    rtos::ThisThread::sleep_for(1000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  blinkThread.start(blinkTask);
  printThread.start(printTask);
}

void loop() {
}
