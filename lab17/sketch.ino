#include <Arduino.h>
#include <Arduino_APDS9960.h>

// -------------------- RGB LED Pins --------------------
#define LED_RED    LEDR
#define LED_GREEN  LEDG
#define LED_BLUE   LEDB

// -------------------- Variables --------------------
const int threshold = 20;      // Adjust after testing
int eventCount = 0;

bool handDetected = false;


// -------------------- LED Functions --------------------
/*void rgbOff()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
}*/

void redOn()
{
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
}

void greenOn()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
}

void blinkTick()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}

// -------------------- Setup --------------------
void setup()
{
    Serial.begin(115200);

    while (!Serial);

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    redOn();

    if (!APDS.begin())
    {
        Serial.println("Failed to initialize APDS9960!");
        while (1);

    
    }

    Serial.println("-----------------------------------");
    Serial.println("Proximity Event Counter Started");
    Serial.println("-----------------------------------");
}
void loop()
{
    if (APDS.proximityAvailable())
    {
        int proximity = APDS.readProximity();
        Serial.print("Proximity: ");
        Serial.println(proximity);

        if (proximity > threshold)
        {
            if (!handDetected)
            {
                handDetected = true;

                // Blink tick LED
                blinkTick();

              

                // 11th tick resets everything
              eventCount++;

              if (eventCount >= 11)
              {
                  eventCount = 0;
                  redOn();
              }
              else if (eventCount == 10)
              {
                  greenOn();
              }

                Serial.print("Event Count: ");
                Serial.println(eventCount);
            }
        }
        else
        {
            handDetected = false;
        }
    }

    delay(50);
}
