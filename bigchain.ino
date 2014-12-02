#include "FastLED.h"
#define NUM_LEDS 45
CRGB leds[NUM_LEDS]; //has to be here to be available in all modes

#include "ColorFade.h"

#define DATA_PIN 5

//type of the parse functions
typedef void (*ParsePtr)(void);
typedef void (*ExecutePtr)(void);

enum Mode {
  FADE,
  NUM_MODES //has to be the last entry!!
};


ParsePtr parse[NUM_MODES];//the parse functions of all the modes
ExecutePtr execute[NUM_MODES];
Mode currentMode = FADE;


void setup() { 
  parse[FADE] = colorFadeParseSerial;
  
  execute[FADE] = colorFadeUpdate;
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  
  if(Serial.available() > 0)
  {
    const uint8_t mode = Serial.read();
    currentMode = (Mode)mode;
    parse[currentMode]();
  }
  execute[currentMode]();
  FastLED.show();
}


//parses command from serial 
void executeCommand(const uint8_t cmd)
{
  
}
