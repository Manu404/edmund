#pragma once
#ifndef PCD8544API_INCLUDED
#define PCD8544API_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include "../../ui/resources/font.h"
#include "./output_api.h"

#include <memory>

#define TARGET_FPS 60
#define FRAME_DURATION_MS (1000 / TARGET_FPS)

namespace Edmund {
  namespace Hardware {

    class PCD8544Api : public IPCD8544Api {
      std::unique_ptr<Adafruit_PCD8544> lcd;
      public:
        PCD8544Api(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST) : lcd(std::unique_ptr<Adafruit_PCD8544>(new Adafruit_PCD8544(SCLK, DIN, DC, CS, RST))) { }
        void begin() { lcd->begin(); }
        void initDisplay() { lcd->initDisplay(); }
        void setRotation(byte v) { lcd->setRotation(v); }
        void setContrast(byte c) { lcd->setContrast(c); }
        void setBias(byte b) { lcd-> setBias(b); }
        void setClockDivider(byte d) { SPI.setClockDivider(d); }
        void print(String m) { lcd->print(m); }
        void println(String m) { lcd->println(m); }
        void drawChar(int16_t x, int16_t y, unsigned char c, int16_t fgcolor, int16_t bgcolor) { lcd->drawChar(x, y, c, fgcolor, bgcolor, 1); }
        void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) { lcd->drawBitmap(x, y, bitmap, w, h, color); }
        void drawNumericBitmap(int16_t x, int16_t y, int n, int16_t w, int16_t h, uint16_t color) { lcd->drawBitmap(x, y, Edmund::UI::Resources::numericFont[n], w, h, color); }
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { lcd->drawRect(x, y, w, h, color); }
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { lcd->fillRect(x, y, w, h, color); }
        void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) { lcd->getTextBounds(str, x, y, x1, y1, w, h); }
        void setCursor(int16_t x, int16_t y) { lcd->setCursor(x, y); }
        void setTextColor(uint16_t c) { lcd->setTextColor(c); }
        void clearDisplay() { lcd->clearDisplay(); }
        void display() { lcd->display(); }
        void useSmallFont() { lcd->setFont(&TomThumb); }
        void useMonoBoldFont() { lcd->setFont(&FreeMonoBold9pt7b); }
    };

  }
}
#endif