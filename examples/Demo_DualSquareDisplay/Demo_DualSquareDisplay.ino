/* Demo Code to Run Test Display of Dual Squary ESP32*/
/**********************************************************************
   Display interfacing with ESP32
  
   | ESP32 | Display | Function |
   -----------------------------------------------------------
   | IO12 | LCD1_CLK | Clock pin of SPI interface for Display|
   | IO11 | LCD1_DIN | MOSI (Master OUT Slave IN) pin of SPI interface|
   | IO9  | LCD1_CS | Chip Select pin of SPI interface|
   | IO13 | LCD1_DC| Data/Command (MISO) pin of SPI interface|
   | IO14 | LCD_RST | Reset of display|
   | IO10 | LCD_BL | Backlight of display|
  
   | ESP32 | Display | Function |
   | IO15 | LCD2_CLK | Clock pin of SPI interface for Display|
   | IO6  | LCD2_DIN | MOSI (Master OUT Slave IN) pin of SPI interface|
   | IO21 | LCD2_CS | Chip Select pin of SPI interface|
   | IO7  | LCD2_DC| Data/Command (MISO) pin of SPI interface|
   | IO18 | LCD_RST | Reset of display|
   | IO48 | LCD_BL | Backlight of display|
 
************************************************************************/
//Import required libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Main board Display SPI pins
#define TFT_CS         9
#define TFT_MOSI       11
#define TFT_SCLK       12
#define TFT_RST        14
#define TFT_DC         13
#define BACKLIGHT      10

// Common board Display SPI pins
#define TFT_CS1         21
#define TFT_MOSI1       17
#define TFT_SCLK1       15
#define TFT_RST1        18
#define TFT_DC1         7
#define BACKLIGHT1      48

//create instance for SPI Display 
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7789 tft1 = Adafruit_ST7789(TFT_CS1, TFT_DC1, TFT_MOSI1, TFT_SCLK1, TFT_RST1);


float p = 3.1415926;
void setup(void) {
  Serial.begin(115200);
  Serial.print(F("Hello! Dual Squary ESP32 Display Test"));
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, HIGH);

  pinMode(BACKLIGHT1, OUTPUT);
  digitalWrite(BACKLIGHT1, HIGH);

  tft.init(240, 240);           // Init ST7789 240x240
  tft1.init(240, 240);           // Init ST7789 240x240

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  //tft.setSPISpeed(40000000);

  Serial.println(F("Initialized"));
  tft.fillScreen(ST77XX_BLACK);
  tft1.fillScreen(ST77XX_BLACK);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  tft1.fillScreen(ST77XX_BLACK);
  testdrawtext("Hello!", ST77XX_WHITE);
  delay(500);

  testdrawrects(ST77XX_YELLOW);
  testdrawcircles(4, ST77XX_GREEN);
  Serial.println("done");
  delay(1000);
}

void loop() {
  tft.invertDisplay(true);
  tft1.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  tft1.invertDisplay(false);
  delay(500);
}


void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);

  tft1.setCursor(0, 0);
  tft1.setTextColor(color);
  tft1.setTextWrap(true);
  tft1.print(text);
}

void testdrawrects(uint16_t color) {
  tft1.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft1.width(); x+=6) {
    tft1.drawRect(tft1.width()/2 -x/2, tft1.height()/2 -x/2 , x, x, color);
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}
