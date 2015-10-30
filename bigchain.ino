#include "FastLED.h"
#include "Mode.h"
#define NUM_LEDS 100
#define DATA_PIN 7

#include "Time.h"
CRGB leds[NUM_LEDS]; //has to be here to be available in all modes
uint8_t buffer[NUM_LEDS]; //a shared buffer that can be used by every mode to do whatever it wants with it
uint16_t speed = 0;//has to be available to all modes
uint16_t mode = 0;
uint16_t brightness = 0;

#include "Strobe.h"
#include "ColorFade.h"

//type of the parse functions
typedef void (*ExecutePtr)(void);
typedef void (*InitPtr)(void);

ExecutePtr execute[NUM_MODES];
InitPtr initialize[NUM_MODES];
Mode currentMode = R_STROBE;
Mode lastMode = currentMode;

void setup() 
{ 

  Serial.begin(9600);
  
  initialize[FADE] = colorFadeInit;
  execute[FADE] = colorFadeUpdate;
  
  initialize[BW_STROBE] = bwStrobeInit;
  execute[BW_STROBE] = strobeUpdate;  
  
  initialize[R_STROBE] = rStrobeInit;
  execute[R_STROBE] = strobeUpdate;

  initialize[B_STROBE] = bStrobeInit;
  execute[B_STROBE] = strobeUpdate;

  initialize[G_STROBE] = gStrobeInit;
  execute[G_STROBE] = strobeUpdate;
  
  initialize[RG_STROBE] = rgStrobeInit;
  execute[RG_STROBE] = rgStrobeUpdate;    
  

  initialize[RAND_FADE] = randomColorFadeInit;
  execute[RAND_FADE] = colorFadeUpdate;  

  initialize[FADE_STROBE] = fadeStrobeInit;
  execute[FADE_STROBE] = fadeStrobeUpdate;   
  
  
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
  speed = analogRead(A0);
  brightness = map(analogRead(A2), 0, 1023, 0, 255);
  mode = map(analogRead(A1), 0, 1023, 0, NUM_MODES - 1);
  currentMode = (Mode) mode;
}

void loop() 
{ 
  //digitalWrite(A1, HIGH);
  updateButtons();
  //Serial.println(mode);
  if(currentMode != lastMode)
  {
    lastMode = currentMode;
    initialize[currentMode]();    
  }
  execute[currentMode]();
  FastLED.setBrightness(brightness);
  FastLED.show(); 
}

