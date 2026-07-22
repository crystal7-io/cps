#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;

  int peak = 0;
  for (int i = 0; i < samplesRead; i++) {
    int val = sampleBuffer[i];
    if (val < 0) {
      val = -val;
    }
    if (val > peak) {
      peak = val;
    }
  }
  Serial.println(peak);
}

void setup() {
  Serial.begin(9600);
  PDM.onReceive(onPDMdata);
  PDM.begin(1, 16000);
}

void loop() {
}
