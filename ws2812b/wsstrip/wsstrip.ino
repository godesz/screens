#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    8
#define BRIGHTNESS  16
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 25

uint8_t r=0,g=0,b=0;
uint8_t pos = 0, dir = 1;

int sgn()
{ return random(0,1)*2-1; }

void setup() {
    Serial.begin(9600);
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    for(int i=0;i<8;i++)  leds[i] = CRGB(0,0,0);
    
}


void loop()
{

    r = (r + sgn()*random(1,20))%256;
    g = (g + sgn()*random(1,30))%256;
    b = (b + sgn()*random(1,40))%256;
    
    leds[pos] = CRGB(0,0,0);
    if (pos >= 7) dir*=-1;
    pos = pos+dir;
    leds[pos] = CRGB(r,g,b);
    
    
   /* Serial.print(r); Serial.print(" ");
    Serial.print(g); Serial.print(" ");
    Serial.print(b); Serial.print("\n");*/
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
