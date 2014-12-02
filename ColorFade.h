

struct colorFadeData
{
  uint8_t h;
};

colorFadeData cfData;


void colorFadeParseSerial()
{
  
}

void colorFadeUpdate()
{
  delay(500);
  ++cfData.h;
  for(uint8_t i = 0; i < NUM_LEDS; ++i)
 {
   leds[i].setHue(cfData.h);   
 } 
}
