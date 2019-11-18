
#include <Arduino.h>
#include <U8g2lib.h>
#include "fix_fft.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
//U8G2_NULL u8g2(U8G2_R0);  // null device, a 8x8 pixel display which does nothing
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 12, /* dc=*/ 4, /* reset=*/ 6); // Arduboy (Production, Kickstarter Edition)
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);//U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); // same as the NONAME variant, but maximizes setContrast() range
//U8G2_SSD1306_128X64_ALT0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); // same as the NONAME variant, but may solve the "every 2nd line skipped" problem

char im[128], data[128];
char x = 0, ylim = 60;
int i = 0, val;
float FPS = 0;
int ido = 0, ido2 = 0;
int min=1024, max=0, dat;
char s[]="0.0";
void setup(void) {
  u8g2.begin();
  analogReference(DEFAULT); // Use default (5v) aref voltage.
  ido = millis();
  u8g2.setFont(u8g2_font_6x10_tf);
}

void loop(void) {
  u8g2.clearBuffer();         // clear the internal memory

  min=1024; max=0;
  for (i = 0; i < 128; i++) {
    val = analogRead(A0);
    data[i] = val / 4 - 128;
    im[i] = 0;
    if(val>max) max=val;
    if(val<min) min=val;
  };
  
  fix_fft(data, im, 7, 0);
  for (i = 1; i < 64; i++) { // In the current design, 60Hz and noise
    dat = sqrt(data[i] * data[i] + im[i] * im[i]);
    u8g2.drawLine(i*2 + x, ylim, i*2 + x, ylim - dat); // skip displaying the 0-500hz band completely.
    //u8g2.drawLine(i*2 + x, 63, i*2 + x, random(10,20)); // skip displaying the 0-500hz band completely.
  }; // rather than 1.

  ido2 = millis();
  //FPS = 1000.0/(ido2 - ido);
  dtostrf(1000.0/(ido2 - ido),5,2,s);
  u8g2.drawStr( 3, 20, "FPS: ");
  u8g2.drawStr( 30, 20, s);
  ido = ido2;
  
  //u8g2.drawLine(0, 0, 155, 55);
  u8g2.sendBuffer();          // transfer internal memory to the display
  //delay(1);  
}

