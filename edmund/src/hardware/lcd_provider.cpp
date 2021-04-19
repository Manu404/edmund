#include "lcd_provider.h"
#include "../ui/resources/font.h"

namespace Edmund {
  namespace Hardware {
    void LcdProvider::initScreen() {
      lcd->begin();
      lcd->setContrast(0x7f);
      lcd->setBias(0x7f);
    }

    void LcdProvider::Print(String m) {
      lcd->print(m);
    }

    void LcdProvider::PrintLine(String m) {
      lcd->println(m);
    }

    void LcdProvider::PrintSymbol(int x_pos, int y_pos, const uint8_t* logo) {
      lcd->drawBitmap(x_pos * 9, y_pos * 10, logo, 9, 10, BLACK);
    }

    void LcdProvider::PrintSmallNumeric(int x_pos, int y_pos, int value, uint16_t color, int length) {
      int char_w = 4, char_h = 5;
      int digitsShift = 0, currentValue = 0, maxRange = 3;
      int debug = value == 42;
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

    void LcdProvider::DrawBox(int x, int y, int w, int h, uint16_t color) {
      lcd->fillRect(x, y, w, h, color);
    }

    void LcdProvider::clear() {
      lcd->clearDisplay();
    }

    void LcdProvider::display() {
      lcd->display();
    }
  }
}



