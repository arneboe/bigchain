#include "FastLED.h"
#include <EEPROM.h>
#include "Mode.h"
#define NUM_LEDS 44
#define DATA_PIN 7
#define SPEED_BUTTON 11
#define MODE_BUTTON 12
#define BRIGHTNESS_BUTTON 13

#define SPEED_EEPROM 42
#define MODE_EEPROM 142
#define BRIGHTNESS_EEPROM 242

#include "Time.h"

//distance of each led to (0,0)
uint8_t dist[NUM_LEDS] = {1, 2, 3, 4, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 5, 4, 3,
                          5, 6, 7, 8, 9, 11, 10, 9, 8, 7, 6, 5, 7, 8, 9, 10, 11, 12, 11, 10, 9, 8};

CRGB leds[NUM_LEDS]; //has to be here to be available in all modes
uint8_t buffer[NUM_LEDS]; //a shared buffer that can be used by every mode to do whatever it wants with it
uint16_t speed = 0;//has to be available to all modes
uint16_t brightness = 0;

unsigned long settingsChangedTime = 0;
bool settingsChanged = false;

unsigned long modeChangedTime = 0;
unsigned long brightnessChangedTime = 0;

#include "Strobe.h"
#include "ColorFade.h"
#include "DistFade.h"

//type of the parse functions
typedef void (*ExecutePtr)(void);
typedef void (*InitPtr)(void);

ExecutePtr execute[NUM_MODES];
InitPtr initialize[NUM_MODES];
Mode currentMode = R_STROBE;
Mode lastMode = currentMode;

void setup() 
{ 
  pinMode(SPEED_BUTTON, INPUT_PULLUP);
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  pinMode(BRIGHTNESS_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  
  //read stored data from eeprom
  EEPROM.get(SPEED_EEPROM, speed);
  EEPROM.get(MODE_EEPROM, currentMode);
  if(currentMode < 0 || currentMode >= NUM_MODES)
  {
    currentMode = RAND_FADE;
  }
  EEPROM.get(BRIGHTNESS_EEPROM, brightness);
  
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

  initialize[FADE_STROBE_2] = fadeStrobe2Init;
  execute[FADE_STROBE_2] = fadeStrobe2Update;
  
  initialize[DIST_FADE] = distFadeInit;
  execute[DIST_FADE] = distFadeUpdate;  
  
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

void settingsHaveChanged()
{
  settingsChangedTime =  millis();
  settingsChanged = true;
}

void saveSettings()
{
  //only write to EEPROM if the settings havnt changed for at least 5 seconds
  if(settingsChanged && millis() - settingsChangedTime > 5000)
  {
    EEPROM.put(SPEED_EEPROM, speed);
    EEPROM.put(MODE_EEPROM, currentMode);
    EEPROM.put(BRIGHTNESS_EEPROM, brightness);
    settingsChanged = false;
  }
}

void updateButtons()
{
  //read speed and mode
  if(digitalRead(SPEED_BUTTON) == LOW)//LOW => pressed
  {
    if(speed < 1023)
    {
      ++speed;
    }
    else
    {
      speed = 0;
    }
    settingsHaveChanged();
    return;
  }

  long currentTime = millis();
  
  if(digitalRead(MODE_BUTTON) == LOW && currentTime - modeChangedTime > 500)
  {
    modeChangedTime = currentTime;
    currentMode = (Mode) ((currentMode + 1) % NUM_MODES);
    settingsHaveChanged();
  }

  if(digitalRead(BRIGHTNESS_BUTTON) == LOW)//LOW => pressed
  {
    if(brightness < 1023)
    {
      ++brightness;
    }
    else
    {
      brightness = 0;
    }
    settingsHaveChanged();
    return;
  }
}

void loop() 
{ 
  //digitalWrite(A1, HIGH);
  updateButtons();
  saveSettings();
  //Serial.println(mode);
  if(currentMode != lastMode)
  {
    lastMode = currentMode;
    initialize[currentMode]();    
  }
  execute[currentMode]();
  FastLED.setBrightness(map(brightness, 0, 1023, 0, 255));
  FastLED.show(); 
}

