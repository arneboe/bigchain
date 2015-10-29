#include "FastLED.h"
#include "Mode.h"
#define NUM_LEDS 100
#define DATA_PIN 7

#include "Time.h"
CRGB leds[NUM_LEDS]; //has to be here to be available in all modes
uint8_t buffer[NUM_LEDS]; //a shared buffer that can be used by every mode to do whatever it wants with it
uint16_t speed = 0;//has to be available to all modes

#include "Strobe.h"
#include "ColorFade.h"

//type of the parse functions
typedef void (*ExecutePtr)(void);
typedef void (*InitPtr)(void);

ExecutePtr execute[NUM_MODES];
InitPtr initialize[NUM_MODES];
Mode currentMode = STROBE;
Mode lastMode = currentMode;

void setup() { 
  Serial.begin(9600);
  
  initialize[FADE] = colorFadeInit;
  execute[FADE] = colorFadeUpdate;
  
  initialize[STROBE] = strobeInit;
  execute[STROBE] = strobeUpdate;  
  
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  
  //blink
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i]= CRGB::Red;
  }
  FastLED.show();
  delay(500);
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i]= CRGB::Black;
  }
  FastLED.show();  
  delay(500);

  initialize[currentMode]();
}

void updateButtons()
{
  //read speed and mode
}

void loop() 
{ 
  updateButtons();
  if(currentMode != lastMode)
  {
    lastMode = currentMode;
    initialize[currentMode]();    
  }
  execute[currentMode]();
  FastLED.show();
}

