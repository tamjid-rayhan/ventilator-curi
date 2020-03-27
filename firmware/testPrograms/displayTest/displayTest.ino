/* Developed for ventilator project curi
  Developer : Md. Tamjid Rayhan and Sajib Karmaker, Date: 3/27/2020
  License: Open to public*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
//#include <XTronical_ST7735.h>
#include <SPI.h>

#define TFT_CS        10//15//10
#define TFT_RST        8//89//8 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        9//18// 9

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;
uint16_t nowTime;
uint16_t prevTime = 0;
uint16_t elapsedTime;

char pre_printValue_1[4]= "    ", pre_printValue_2[4]= "    ";
//#define A1 9
//#define A2 10
void setup() {
  Serial.begin(9600);
  Serial.print(F("Hello! ST7735 TFT Test"));

    tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
//  tft.init();
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
  drawInputScreen();

}

void loop() {
  // put your main code here, to run repeatedly:
  nowTime = millis();
  elapsedTime = nowTime - prevTime;
  if (elapsedTime > 500) {
    //    drawInputScreen();
    drawdata();
    prevTime = nowTime;
  }

}

void testdrawtext(char *text, uint16_t color, int xPos, int yPos) {
  tft.setCursor(xPos, yPos);
  tft.setTextColor(color);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.print(text);
}

void testdrawrects(uint16_t color, int xPos, int yPos, int rectLen, int rectWid) {
  //tft.fillScreen(ST77XX_BLACK);
  //  for (int16_t x=0; x < tft.width(); x+=6) {
  //    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  //  }
  tft.drawRect(xPos, yPos, rectLen , rectWid , color);
}

void drawInputScreen() {
  int width = tft.width();
  int height = tft.height();
  tft.fillScreen(ST77XX_BLACK);
  //Draw breathing frequency textbox
  testdrawtext(" Respiratory Rate ", ST77XX_WHITE, 0, 10);
  testdrawtext("      per minute       ", ST77XX_WHITE, 0, 20);
  testdrawrects(ST77XX_WHITE, 5, 30, tft.width() - 10, 15);
  //Draw Tidal volume textbox
  testdrawtext("     Tidal Volume     ", ST77XX_WHITE, 0, 60);
  testdrawtext("      (in Litre)       ", ST77XX_WHITE, 0, 70);
  testdrawrects(ST77XX_WHITE, 5, 80, tft.width() - 10, 15);
}


void clearscreen() {
  tft.fillScreen(ST77XX_BLACK);
}

void drawdata() {
  int width = tft.width();
  int height = tft.height();

  char printVal[4];
  String placeHolder;

  int respiratoryRate = analogRead(A0);
  placeHolder = String(respiratoryRate);
  placeHolder.toCharArray(printVal, 4);
  testdrawtext(pre_printValue_1, ST77XX_BLACK, width / 2 - 2, 32);
  testdrawtext(printVal, ST77XX_WHITE, width / 2 - 2, 32);
  Serial.println(respiratoryRate);
  placeHolder.toCharArray(pre_printValue_1, 4);
  int tidalVolume = analogRead(A1);
  placeHolder = String(tidalVolume);
  placeHolder.toCharArray(printVal, 4);
  testdrawtext(pre_printValue_2, ST77XX_BLACK, width / 2 - 2, 82);
  testdrawtext(printVal, ST77XX_WHITE, width / 2 - 2, 82);
  Serial.println(tidalVolume);
  placeHolder.toCharArray(pre_printValue_2, 4);
}