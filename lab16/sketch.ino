#include <nrf.h>

int ledPin = 2;

extern "C" void TIMER4_IRQHandler(void) {
  if (NRF_TIMER4->EVENTS_COMPARE[0]) {
    NRF_TIMER4->EVENTS_COMPARE[0] = 0;
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);

  NRF_TIMER4->TASKS_STOP = 1;
  NRF_TIMER4->MODE = TIMER_MODE_MODE_Timer;
  NRF_TIMER4->BITMODE = TIMER_BITMODE_BITMODE_32Bit;
  NRF_TIMER4->PRESCALER = 9;
  NRF_TIMER4->CC[0] = 1000000;
  NRF_TIMER4->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Msk;
  NRF_TIMER4->INTENSET = TIMER_INTENSET_COMPARE0_Msk;

  NVIC_EnableIRQ(TIMER4_IRQn);
  NRF_TIMER4->TASKS_START = 1;
}

void loop() {
}
