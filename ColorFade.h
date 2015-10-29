static uint16_t colorFadeDelay = 100;

void colorFadeInit()
{
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = 0;
  }
}

void colorFadeUpdate()
{
  WAIT(cfData.delay);
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
 {
   ++buffer[i];
   leds[i].setHue(buffer[i]);   
 } 
}
