#include <FastLED.h>
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define LED_PIN     4
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    64

#define BRIGHTNESS  4
#define FRAMES_PER_SECOND 10

uint8_t x = 0, y = 0;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  for(int i = 0 ; i<NUM_LEDS; i++) leds[i] = CRGB(0,0,0);
  FastLED.show();
}

uint8_t get_val(uint8_t xt, uint8_t yt)
{
  
uint8_t v1 = 0;
v1 = yt*8;
if (yt % 2 == 1) v1+=xt;
else v1+=8-xt;
 return v1;
}

uint8_t pm()
{
  return (random(0,3))-1;
}

void loop()
{
  //leds[get_val(x,y)] = CRGB(0,0,0);

  //if (random(0,2) == 0) x = (x + pm())%8;
  //else y = (y + pm())%8;
  

  leds[get_val(x,y)] = CRGB(0,0,64);
  x = x + 1;
  if (x % 8 == 0) { y++; x = 0; }
  Serial.print(x);
  Serial.print(" ");
  Serial.println(y);
  
  FastLED.show(); // display this frame
  FastLED.delay(500);
}

