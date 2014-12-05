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
  uint8_t snakePos;
  int8_t snakeDir;
  uint8_t currentArea;
  bool areasOut;
} stData;

#define NUM_AREAS 11
static int8_t areas[NUM_AREAS][7] = {{1,2,3,4,-1, 0, 0},
                                      {5,7,8,9,10, 11, -1},
                                      {6,12,13,14,-1, -1, 0},
                                      {0,15,16,17,18, -1, 0},
                                      {19,20,21,22,23, -1, 0},
                                      {24,25,26,-1,-1, 0, 0},
                                      {27,28,29,-1,-1, 0, 0},
                                      {30,31,32,33,34, -1, 0},
                                      {35,36,37,-1,34, -1, 0},
                                      {38,39,40,41,-1, -1, 0},
                                      {42,43,44,-1,-1, -1, 0}};

void strobeInit()
{
  stData.delay = 255;
  stData.on = true;
  stData.mode = STROBE_AREA;
  stData.left = true;
  stData.onColor = CRGB::White;
  stData.offColor = CRGB::Black;
  stData.color = false;
  stData.onHue = 0;
  stData.snakePos = 0;
  stData.snakeDir = 1;
  stData.currentArea = 0;
  stData.areasOut = true;
}

void strobeParseSerial()
{
  waitForBytes(3);
  
  const uint8_t speed = Serial.read(); //from 10 to 200 bpm
  float bpms = float(speed) / 60.0;
  bpms /= 1000.0;
  float delayf = 1.0 / bpms;
  delayf /= 2.0;
  delayf *= 1.23; 
  stData.delay = delayf;
  stData.mode = (StrobeMode)Serial.read();
  stData.color = Serial.read();
  
  if(stData.color)
  {
    stData.onColor.setHue(stData.onHue);
    stData.offColor = CRGB::Black;
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
  stData.snakePos += stData.snakeDir;
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

void turnOnArea(const int i)
{
  int j = 0;
  while(areas[i][j] != -1)
  {
    leds[areas[i][j]] = stData.onColor;
    ++j;
  }
}

void strobeArea()
{
  turnOffAll();
  if(stData.areasOut)
  {
    const int left = stData.currentArea;
    const int right = (NUM_AREAS - 1) - left;
    turnOnArea(left);
    turnOnArea(right);
    
    if(stData.currentArea == (NUM_AREAS / 2))
    {
      stData.areasOut = false;
    }
    else
    {
      ++stData.currentArea;
    }
  }
  else
  {
    const int left = stData.currentArea;
    const int right = (NUM_AREAS - 1) - left;
    turnOnArea(left);
    turnOnArea(right);
    if(stData.currentArea == 0)
    {
      stData.areasOut = true;
    }
    else
    {
      --stData.currentArea;
    }
  }
}

void strobeUpdate()
{
  WAIT(stData.delay);
  
  if(stData.color)
  {
    stData.onHue += 65; //same as +130 every 2 frame
    stData.onColor.setHue(stData.onHue);
    stData.offColor = CRGB::Black;
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
    case STROBE_AREA:
      strobeArea();
      break;
    }  
}

