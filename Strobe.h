
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
  strobeDelay = 1024 + strobeFlashDuration - speed;
  if(strobeWhite)
  {
    WAIT(strobeFlashDuration);
    strobeWhite = false;
    strobeOff();
  }
  else
  {
    WAIT(strobeDelay);
    strobeWhite = true;
    strobeOn();
  }
}

