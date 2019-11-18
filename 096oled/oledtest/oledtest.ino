

#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h>

//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 4);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, 4);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 4);
//U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, 4); 

void setup() {
  u8g2.begin();
  delay(1000);
}

void loop() {
  delay(10);
  u8g2.clearBuffer();          // clear the internal memory
  delay(10);
  //u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  //u8g2.drawStr(0,35,"Hello World!");  // write something to the internal memory

  u8g2.setDrawColor(1);
  delay(10);
  u8g2.drawLine(0, 0, 0, 63);
  u8g2.drawLine(0, 0, 127, 0);
  u8g2.drawLine(0, 63, 127, 63);
  u8g2.drawLine(127, 0, 127, 63);
delay(10);
  u8g2.drawLine(0, 0, 127, 63);
   u8g2.sendBuffer();          // transfer internal memory to the display
   u8g2.clearBuffer();
delay(10);

  while(1);
}


/*
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {

  display.clearDisplay();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Wire.begin();
  display.clearDisplay();

  delay(2000);

  //for(int16_t i=50; i<150; i++) display.write(i);
  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(0, 0, 127, 0, WHITE);
  display.drawLine(0, 63, 127, 63, WHITE);
  display.drawLine(127, 0, 127, 63, WHITE);

  display.drawLine(0, 0, 127, 63, WHITE);


   display.display();
}

void loop() {}




/*#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

//Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
//Adafruit_SSD1306 display(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display;
uint16_t array_sds[64];
int i = 0; 

void draw_lines(uint16_t *datas)
{
display.clearDisplay();
for(i=0;i<64;i++)
{
display.drawLine(i, 0, i, datas[i], WHITE);
display.drawLine(i+1, 0, i+1, datas[i], WHITE);
}

display.display();
}

void setup() {
  //Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Wire.begin();

  delay(2000);
  //for(i=0;i<64;i++) array_sds[i]=0;  
}

void loop() {
  //Serial.print("Looping...\n");
  
  display.drawLine(1, i, 63, 63-i, WHITE);
  i = (i+1)%64;
    display.display();
    display.clearDisplay();
    delay(20);
}

/*  display.drawLine(0, 0, i, display.height()-1, WHITE);
  
  display.clearDisplay();
  delay(2000); // Pause for 2 seconds

    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, INVERSE);
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
  
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  display.println(3.141592);*/ 
