#include <Arduino.h>
#include "nrf.h"

// Variable to store LED state
volatile bool ledState = false;

//--------------------------------------------------
// TIMER4 Interrupt Service Routine
//--------------------------------------------------
extern "C" void TIMER4_IRQHandler(void)
{
    // Check Compare0 Event
    if (NRF_TIMER4->EVENTS_COMPARE[0])
    {
        // Clear Compare Event
        NRF_TIMER4->EVENTS_COMPARE[0] = 0;

        // Toggle LED
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
    }
}

void setup()
{
    // Configure Built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    //--------------------------------------------------
    // Configure TIMER4
    //--------------------------------------------------

    // Stop timer before configuration
    NRF_TIMER4->TASKS_STOP = 1;

    // Clear timer count
    NRF_TIMER4->TASKS_CLEAR = 1;

    // Timer Mode
    NRF_TIMER4->MODE = TIMER_MODE_MODE_Timer;

    // 32-bit Timer
    NRF_TIMER4->BITMODE = TIMER_BITMODE_BITMODE_32Bit;

    // Prescaler = 4
    // Timer frequency = 16 MHz / 16 = 1 MHz
    NRF_TIMER4->PRESCALER = 4;

    // Compare value for 1 second
    NRF_TIMER4->CC[0] = 1000000;

    // Auto clear timer after compare match
    NRF_TIMER4->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Msk;

    // Clear any pending event
    NRF_TIMER4->EVENTS_COMPARE[0] = 0;

    // Enable Compare0 interrupt
    NRF_TIMER4->INTENSET = TIMER_INTENSET_COMPARE0_Msk;

    //--------------------------------------------------
    // Configure NVIC
    //--------------------------------------------------

    NVIC_ClearPendingIRQ(TIMER4_IRQn);
    NVIC_SetPriority(TIMER4_IRQn, 1);
    NVIC_EnableIRQ(TIMER4_IRQn);

    //--------------------------------------------------
    // Start TIMER4
    //--------------------------------------------------

    NRF_TIMER4->TASKS_START = 1;
}

void loop()
{
    // Nothing required.
    // LED blinking is handled entirely by TIMER4 interrupt.
}