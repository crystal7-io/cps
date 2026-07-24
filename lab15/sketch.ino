#include <PDM.h>

constexpr int SOUND_THRESHOLD = 300;
short sampleBuffer[256];
volatile int samplesRead = 0;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM microphone.");
    while (true) {}
  }
}

void loop() {
  if (!samplesRead) return;

  int level = 0;
  for (int i = 0; i < samplesRead; i++) {
    level = max(level, abs(sampleBuffer[i]));
  }
  bool loud = level > SOUND_THRESHOLD;
  // RGB LED channels are active LOW: green for loud, red for quiet.
  digitalWrite(LEDR, loud ? HIGH : LOW);
  digitalWrite(LEDG, loud ? LOW : HIGH);
  Serial.println(level);
  samplesRead = 0;
}
