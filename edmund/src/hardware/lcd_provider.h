#pragma once
#ifndef LCDPROVIDER_INCLUDED
#define LCDPROVIDER_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/TomThumb.h>
#include "../ui/resources/font.h"

#define TARGET_FPS 120
#define FRAME_DURATION_MS 1000 / TARGET_FPS

namespace Edmund {
  namespace Hardware {
    class LcdProvider
    {
    public:
      LcdProvider(Adafruit_PCD8544* _lcd) : lcd(_lcd) { }
      void Print(String m);
      void PrintLine(String m);
      void PrintSymbol(int x_pos, int y_pos, const uint8_t* logo);
      void PrintNumberSmall(int x_pos, int y_pos, int value, uint16_t color, int length);
      void DrawScreen(const uint8_t* screen);
      void DrawBox(int x, int y, int w, int h, uint16_t color);
      void DrawBorder(int x, int y, int w, int h, uint16_t color);

      void PrintIntLarge(int x, int y, u_int value, uint16_t color, int length) {
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

      void PrintMenuOption(int x, int y, String m) {
        lcd->println(m);
        lcd->setFont(&TomThumb);
        lcd->setCursor(x, y);
        lcd->println(m);
      }

    protected:
      void initScreen();
      void clear();
      void display();
    private:
      Adafruit_PCD8544* lcd;
    };
  }
}
#endif