#include "FastLED.h"
#define NUM_LEDS 50
#define DATA_PIN 5

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  	 FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  Serial.println("test");
  // Turn the LED on, then pause
  for(int i = 0; i < NUM_LEDS; ++i)
    leds[i] = CRGB::Blue;
  FastLED.show();
  delay(200);
  // Now turn the LED off, then pause

}
