
static uint16_t strobeDelay = 2000;//delay in ms
static uint16_t lastSpeed = speed;
static uint16_t strobeFlashDuration = 130;//time the light is on
static boolean strobeWhite = false;

void strobeInit()
{}

//stData.onColor = CRGB::White;
//stData.offColor = CRGB::Black;

void strobeOn()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = CRGB::White;
  }  
}

void strobeOff()
{
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = CRGB::Black;
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

