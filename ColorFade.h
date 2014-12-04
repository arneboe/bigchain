struct colorFadeData
{
  uint8_t h;
  uint16_t delay;
} cfData;

void colorFadeInit()
{
  cfData.h = 0;
  cfData.delay = 100;
  
  //init buffer
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = 0;
  }
}

void colorFadeParseSerial()
{
  waitForBytes(2);
  
  const uint8_t speed = Serial.read(); //from 0 to 100. 100 = full speed
  const uint8_t scramble = Serial.read(); //if 1 the buffer will be scrambled, if 2 the buffer will be reset, otherwise buffer will not be changed
  
  cfData.delay = map(speed, 100, 0, 0, 500);
  
  if(scramble == 1)
  {
    for(uint8_t i = 0; i < NUM_LEDS; ++i)
    {
      buffer[i] = random(0, 256);
    }    
  }
  else if(scramble == 2)
  {
    for(uint8_t i = 0; i < NUM_LEDS; ++i)
    {
      buffer[i] = 0;
    }       
  }
}

void colorFadeUpdate()
{
  WAIT(cfData.delay);
  ++cfData.h;
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
 {
   ++buffer[i];
   leds[i].setHue(buffer[i]);   
 } 
}
