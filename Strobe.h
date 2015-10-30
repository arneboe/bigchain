
static uint16_t strobeDelay = 2000;//delay in ms
static uint16_t lastSpeed = speed;
static uint16_t strobeFlashDuration = 20;//time the light is on
static boolean strobeWhite = false;
static CRGB strobeOnColor = CRGB::White;
static CRGB strobeOffColor = CRGB::Black;

void bwStrobeInit()
{
  strobeOnColor = CRGB::White;
  strobeOffColor = CRGB::Black;
}

void rStrobeInit()
{
  strobeOnColor = CRGB::Red;
  strobeOffColor = CRGB::Black;
}

void bStrobeInit()
{
  strobeOnColor = CRGB::MediumBlue;
  strobeOffColor = CRGB::Black;
}

void gStrobeInit()
{
  strobeOnColor = CRGB::Green;
  strobeOffColor = CRGB::Black;
}

void fadeStrobeInit()
{
  strobeOnColor.setHue(onHue);
  strobeOffColor.setHue(offHue);
}

void rgStrobeInit()
{
  strobeOnColor = CRGB::Red;
  strobeOffColor = CRGB::Green;
}


//stData.onColor = CRGB::White;
//stData.offColor = CRGB::Black;

void strobeOn()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = strobeOnColor;
  }  
}

void strobeOff()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = strobeOffColor;
  }    
}

void fadeStrobeUpdate()
{  
  const uint16_t t = 1024 - speed; 
  static uint8_t h = 0; 
  WAIT(t);
  h += 124;
  strobeOffColor.setHue(h);
  strobeOff();
}

void rgStrobeUpdate()
{  
  const uint16_t t = 1024 - speed; 
  static uint8_t h = 0; 
  static bool on = false;
  WAIT(t);
  if(on)
  {
    strobeOffColor = CRGB::Red;
    strobeOff();
    on = false;
  }
  else
  {
    strobeOffColor = CRGB::Green;
    strobeOff();
    on = true;    
  }
}


void strobeUpdate()
{  
  static unsigned long lastTime = 0;
  static unsigned long currentTime = 0;
  currentTime = millis();
  
  strobeDelay = 1024 - speed;  

  if(strobeWhite && (currentTime - lastTime) > strobeFlashDuration)
  {
    lastTime = currentTime;
    strobeWhite = false;
    strobeOff();
    
  }
  else if(!strobeWhite && (currentTime - lastTime) > strobeDelay)
  {
    lastTime = currentTime;
    strobeWhite = true;
    strobeOn();
  }
}

