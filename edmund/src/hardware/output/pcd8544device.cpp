#include "pcd8544device.h"

int is_init = 0;
namespace Edmund {
  namespace Hardware {
    void PCD8544OutputDevice::initScreen() {
      if (is_init == 1) return;
      lcd->begin();
      lcd->initDisplay();
      lcd->setRotation(2);
      lcd->setContrast(64);
      lcd->setBias(4);
      lcd->setTextColor(1);
      is_init = 1;
    }

    void PCD8544OutputDevice::Print(String m) const {
      lcd->print(m);
    }

    void PCD8544OutputDevice::Print(String m, int x, int y) const {
      lcd->setCursor(x, y);
      this->Print(m);
    }

    void PCD8544OutputDevice::PrintLine(String m) const {
      lcd->println(m);
    }

    void PCD8544OutputDevice::PrintLineCentered(const String& buf, int x, int y, uint16_t color) const
    {
      int16_t x1, y1;
      uint16_t w, h;
      lcd->useSmallFont();
      lcd->getTextBounds(buf, 0, y, &x1, &y1, &w, &h);
      lcd->setCursor(x - (w / 2), y);
      lcd->setTextColor(color);
      lcd->print(buf);
    }

    void PCD8544OutputDevice::DrawSymbol(int x, int y, const uint8_t* logo) const {
      lcd->drawBitmap(x * 9, y * 10, logo, 9, 10, BLACK);
    }

    void PCD8544OutputDevice::DrawScreen(const uint8_t* logo) const {
      lcd->drawBitmap(0, 0, logo, 84, 48, BLACK);
    }

    void PCD8544OutputDevice::DrawScreen(const uint8_t* logo, int x = 0) const {
      lcd->drawBitmap(x, 0, logo, 84, 48, BLACK);
    }    
    
    void PCD8544OutputDevice::DrawLogo(int x, int y, int w, int h, const uint8_t* logo) const {
      lcd->drawBitmap(x, y, logo, w, h, BLACK);
    }

    void PCD8544OutputDevice::DrawBox(int x, int y, int w, int h, uint16_t color) const {
      lcd->fillRect(x, y, w, h, color);
    }

    void PCD8544OutputDevice::DrawBorder(int x, int y, int w, int h, uint16_t color) const {
      lcd->drawRect(x, y, w, h, color);
    }

    void PCD8544OutputDevice::clear() const {
      lcd->clearDisplay();
    }

    void PCD8544OutputDevice::display() const {
      lcd->display();
    }

    void PCD8544OutputDevice::PrintNumberLarge(int x, int y, int value, uint16_t color, int minLength) const {
      lcd->useMonoBoldFont();
      int remainingValue = std::abs(value), currentDigit = 0, printedDigitCount = 0;
      if(value < 0) {
        lcd->fillRect(x - 5, y + 10, 2, 2, color);
        x += 3;
      }

      for (int i = 5; remainingValue >= 0 && i >= 0; i--) // 16bits uint, 5 digits max
      {
        int p = std::pow(10, i);
        currentDigit = (remainingValue / p);
        remainingValue %= p;
        if (currentDigit > 10 || (currentDigit == 0 && printedDigitCount == 0 && i >= minLength))
          continue;
        lcd->drawChar(x + (printedDigitCount * 8), y + 10, (char)(currentDigit + ((int)'0')), color, !color);
        printedDigitCount += 1;
      }
    };

    void PCD8544OutputDevice::PrintNumberSmall(int x, int y, int value, uint16_t color, int minLength) const {
      int char_w = 4, char_h = 5;
      int printedDigitCount = 0, currentDigit = 0, maxRange = 3;
      value = std::abs(value);

      for (int i = 1; i <= maxRange; i++) {
        int p = std::pow(10, i);
        currentDigit = (value % p) / (p / 10);
        value -= currentDigit;
        if ((minLength - i) < 0) continue;
        if (!(currentDigit == 0 && i == 3)) // don't print on leading 0 for hundred
          lcd->drawNumericBitmap(x + (char_w * ((minLength - printedDigitCount) - 1)) - (i < 3 && minLength == 3), y, currentDigit, char_w, char_h, color);
        printedDigitCount += 1;
      }
    };
  }
}



