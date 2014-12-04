#include "StrobeMode.h"
struct StrobeData
{
  uint16_t delay;  
  bool on;
  StrobeMode mode;
  bool left; //used in strobe half
  bool color;
  CRGB onColor;
  CRGB offColor;
  uint8_t onHue;
  uint8_t offHue;
  uint8_t snakePos;
  int8_t snakeDir;
} stData;


void strobeInit()
{
  stData.delay = 255;
  stData.on = true;
  stData.mode = STROBE_NORMAL;
  stData.left = true;
  stData.onColor = CRGB::White;
  stData.offColor = CRGB::Black;
  stData.color = false;
  stData.onHue = 0;
  stData.offHue = 128;
  stData.snakePos = 0;
  stData.snakeDir = 1;
}

void strobeParseSerial()
{
  waitForBytes(3);
  
  const uint8_t speed = Serial.read(); //from 0 to 100. 100 = full speed  
  stData.delay = map(speed, 100, 0, 0, 600);  
  stData.mode = (StrobeMode)Serial.read();
  stData.color = Serial.read();
  
  if(stData.color)
  {
    stData.onColor.setHue(stData.onHue);
    stData.offColor.setHue(stData.offHue);
  }
  else
  {
    stData.onColor = CRGB::White;
    stData.offColor = CRGB::Black;
  }
}


void strobeOn(const int start, const int end)
{
  for(int i = start; i < end; ++i)
  {
    leds[i] = stData.onColor;
  }  
}

void strobeOff(const int start, const int end)
{
  for(int i = start; i < end; ++i)
  {
    leds[i] = stData.offColor;
  }    
}


void strobeNormal()
{
  WAIT(stData.delay);
  if(stData.on)
  {
    strobeOff(0, NUM_LEDS);
    stData.on = false;
  }
  else
  {
    strobeOn(0, NUM_LEDS);
    stData.on = true;
  }
}

void turnOffAll()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = CRGB::Black;
  }   
}

void strobeHalf()
{
  if(stData.left)
  {//turn on left
    stData.left = false;
    strobeOff(0, 27);
    leds[27] = CRGB::Black;
    leds[28] = CRGB::Black;
    strobeOn(29, NUM_LEDS);
  }
  else
  {
    stData.left = true;
    strobeOn(0, 27);   
    leds[27] = CRGB::Black;
    leds[28] = CRGB::Black;
    strobeOff(29, NUM_LEDS);
  } 
}

void strobeRandom()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    if(random(0, 100) < 25)
    {
      leds[i] = stData.onColor;
    }
    else
    {
      leds[i] = stData.offColor;
    }
  }
}

void strobeSnake()
{
  stData.snakePos += stData.snakeDir * 3;
  if(stData.snakePos >= 43)
  {
    stData.snakeDir = -1;
  }
  else if(stData.snakePos <= 0)
  {
    stData.snakeDir = 1;
  }
  strobeOff(0, NUM_LEDS);
  leds[stData.snakePos] = stData.onColor;
  leds[stData.snakePos + 1] = stData.onColor;
  leds[stData.snakePos + 2] = stData.onColor;
}

void strobeUpdate()
{
  WAIT(stData.delay);
  
  if(stData.color)
  {
    ++stData.onHue;
    ++stData.offHue;
    stData.onColor.setHue(stData.onHue);
    stData.offColor.setHue(stData.offHue);
  }
  
  switch(stData.mode)
  {
    case STROBE_NORMAL:
      strobeNormal();
      break;
    case STROBE_HALF:
      strobeHalf();
      break;
    case STROBE_RANDOM:
      strobeRandom();
      break;
    case STROBE_SNAKE:
      strobeSnake();
      break;
  }  
}

