#include "lcd_provider.h"
#include "../ui/resources/font.h"

namespace Edmund {
  namespace Hardware {
    void LcdProvider::initScreen() {
      lcd->begin();
      lcd->initDisplay();
      lcd->setRotation(2);
      lcd->setContrast(64);
      lcd->setBias(4);
      SPI.setClockDivider(1);
    }

    void LcdProvider::Print(String m) {
      lcd->print(m);
    }

    void LcdProvider::PrintLine(String m) {
      lcd->println(m);
    }

    void LcdProvider::PrintIntLarge(int x, int y, u_int value, uint16_t color, int length) {
      lcd->setFont(&FreeMonoBold9pt7b);
      int remainingValue = value, currentValue = 0, decimal_shift = 0;
      for (int i = 5; remainingValue >= 0 && i >= 0; i--) // 16bits int, 5 digits max
      {
        int p = pow(10, i);
        currentValue = (remainingValue / p);
        remainingValue %= p;
        if (currentValue > 10 || (currentValue == 0 && decimal_shift == 0 && i >= length))
          continue;
        lcd->drawChar(x + (decimal_shift * 8), y + 10, (char)(currentValue + ((int)'0')), color, !color, 1);
        decimal_shift += 1;
      }
    }

    void LcdProvider::PrintLineCentered(const String& buf, int x, int y, uint16_t color)
    {
      int16_t x1, y1;
      uint16_t w, h;
      lcd->setFont(&TomThumb);
      lcd->getTextBounds(buf, 0, y, &x1, &y1, &w, &h);
      lcd->setCursor(x - (w / 2), y);
      lcd->setTextColor(color);
      lcd->print(buf);
    }

    void LcdProvider::PrintSymbol(int x_pos, int y_pos, const uint8_t* logo) {
      lcd->drawBitmap(x_pos * 9, y_pos * 10, logo, 9, 10, BLACK);
    }

    void LcdProvider::PrintNumberSmall(int x_pos, int y_pos, int value, uint16_t color, int length) {
      int char_w = 4, char_h = 5;
      int digitsShift = 0, currentValue = 0, maxRange = 3;

      for (int i = 1; i <= maxRange; i++) {
        int p = pow(10, i);
        currentValue = (value % p) / (p / 10);
        value = value - currentValue;
        if ((length - i) < 0) continue;
        if (!(currentValue == 0 && i == 3)) // don't print on leading 0 for hundred
          lcd->drawBitmap(x_pos + (char_w * ((length - digitsShift) - 1)) - (i < 3 && length == 3), y_pos, Edmund::UI::Resources::numericFont[currentValue], char_w, char_h, color);
        digitsShift += 1;
      }
    }

    void LcdProvider::DrawScreen(const uint8_t* logo) {
      lcd->drawBitmap(0, 0, logo, 84, 48, BLACK);
    }

    void LcdProvider::DrawScreen(const uint8_t* logo, int x) {
      lcd->drawBitmap(x, 0, logo, 84, 48, BLACK);
    }    
    
    void LcdProvider::DrawLogo(int x, int y, int w, int h, const uint8_t* logo) {
      lcd->drawBitmap(x, y, logo, w, h, BLACK);
    }

    void LcdProvider::DrawBox(int x, int y, int w, int h, uint16_t color) {
      lcd->fillRect(x, y, w, h, color);
    }

    void LcdProvider::DrawBorder(int x, int y, int w, int h, uint16_t color) {
      lcd->drawRect(x, y, w, h, color);
    }

    void LcdProvider::clear() {
      //fill(BLACK);
      lcd->clearDisplay();
    }

    void LcdProvider::display() {
      lcd->display();
    }
  }
}



