#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    8
#define BRIGHTNESS  16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 5

uint16_t i = 0, j = 0;
uint8_t mat[8][3];

void test1()
{
  j = (j+1)%9;

    leds[j] = CRGB(random(0,255),random(0,255),random(0,255));      

    if (j==8) for(i=0;i<8;i++)
    {
      leds[i] = CRGB(0,0,0);      
      j=0;
    }
}

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}


void loop()
{
    j = random(0,8);

    leds[j] = CRGB(random(0,255),random(0,255),random(0,255));      

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

