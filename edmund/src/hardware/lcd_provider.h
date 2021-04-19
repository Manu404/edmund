#pragma once
#ifndef LCDPROVIDER_INCLUDED
#define LCDPROVIDER_INCLUDED

#include <Adafruit_GFX.h> 
#include <Adafruit_PCD8544.h> 

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
      void PrintSmallNumeric(int x_pos, int y_pos, int value, uint16_t color, int length);
      void DrawScreen(const uint8_t* screen);
      void DrawBox(int x, int y, int w, int h, uint16_t color);
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