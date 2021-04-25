#pragma once
#ifndef LCDPROVIDER_INCLUDED
#define LCDPROVIDER_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/TomThumb.h>
#include "../ui/resources/font.h"

#define TARGET_FPS 60
#define FRAME_DURATION_MS (1000 / TARGET_FPS)

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
      void DrawScreen(const uint8_t* logo, int x);
      void DrawLogo(int x, int y, int w, int h, const uint8_t* logo);
      void PrintNumberLarge(int x, int y, u_int value, uint16_t color, int length);
      void PrintLineCentered(const String& buf, int x, int y, uint16_t color);
      int GetScreenWidth() { return 84; }
      int GetScreenHeigt() { return 48; }

    protected:
      void initScreen();
      void clear();
      void display();

      void beginFrame() {
        clear();
      }

      void endFrame() {
        display();
      }
    private:
      Adafruit_PCD8544* lcd;
    };
  }
}
#endif