static uint16_t distFadeDelay = 100;

void distFadeInit()
{
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = dist[i] * 3;
  }
}

void distFadeUpdate()
{
  distFadeDelay = 1024 - speed;
  distFadeDelay /= 2;
  WAIT(distFadeDelay);
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
 {
   buffer[i] += 1;
   leds[i].setHue(buffer[i]);   
 } 
}
