struct StrobeData
{
  uint8_t delay;  
  bool on;
} stData;


void strobeInit()
{
  stData.delay = 255;
  stData.on = true;
}

void strobeParseSerial()
{
  
}


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
  WAIT(stData.delay);
  if(stData.on)
  {
    strobeOff();
    stData.on = false;
  }
  else
  {
    strobeOn();
    stData.on = true;
  }
  
}

