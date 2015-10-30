static uint16_t colorFadeDelay = 100;

void colorFadeInit()
{
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = 0;
  }
}

void randomColorFadeInit()
{
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = random(0, 255);
  }
}

void colorFadeUpdate()
{
  colorFadeDelay = 1024 - speed;
  WAIT(colorFadeDelay);
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
 {
   buffer[i] += 3;
   leds[i].setHue(buffer[i]);   
 } 
}
