#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead;
volatile int peak;
int redPin = 2;
int greenPin = 3;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;

  peak = 0;
  for (int i = 0; i < samplesRead; i++) {
    int val = sampleBuffer[i];
    if (val < 0) {
      val = -val;
    }
    if (val > peak) {
      peak = val;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, HIGH);
  PDM.onReceive(onPDMdata);
  PDM.begin(1, 16000);
}

void loop() {
  if (peak > 300) {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}
