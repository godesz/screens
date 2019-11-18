

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))

  uint16_t x1,y1,x2,y2, line = 0;

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);


  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  Serial.println("done");
  delay(1000);
}

void loop() {
  //tft.invertDisplay(true);
  line = (line +1 ) %160;
  tft.drawLine(0, line, 128, line, RGB(0,0,0));
  x1 = 0;
  y1 = line;
  x2 = random(20,100);
  y2 = line;
  tft.drawLine(x1, y1, x2, y2, RGB(100,100,100));
  delay(10);
}

/*
  tft.fillScreen(ST77XX_BLACK);
  tft.drawFastHLine(0, y, tft.width(), color1);
  tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
  tft.fillCircle(x, y, radius, color);
  tft.drawCircle(x, y, radius, color);*/
