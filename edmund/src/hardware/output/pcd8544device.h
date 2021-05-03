#pragma once
#ifndef LCDPROVIDER_INCLUDED
#define LCDPROVIDER_INCLUDED

#include "outputapi.h"

#include <memory>

#define TARGET_FPS 60
#define FRAME_DURATION_MS (1000 / TARGET_FPS)

namespace Edmund {
  namespace Hardware {

    class PCD8544OutputDevice : public IOutputDevice
    {
    private:
      std::unique_ptr<IPCD8544Api> lcd;
    public:
      PCD8544OutputDevice(std::unique_ptr<IPCD8544Api> _lcd) 
        : lcd(std::move(_lcd)) 
      { }

      void Print(String m) const; 
      void Print(String m, int x, int y) const;
      void PrintLine(String m) const;
      void DrawSymbol(int x_pos, int y_pos, const uint8_t* logo) const;
      void PrintNumberSmall(int x_pos, int y_pos, int value, uint16_t color, int length) const;
      void DrawScreen(const uint8_t* screen) const;
      void DrawBox(int x, int y, int w, int h, uint16_t color) const;
      void DrawBorder(int x, int y, int w, int h, uint16_t color) const;
      void DrawScreen(const uint8_t* logo, int x) const;
      void DrawLogo(int x, int y, int w, int h, const uint8_t* logo) const;
      void PrintNumberLarge(int x, int y, u_int value, uint16_t color, int length) const;
      void PrintLineCentered(const String& buf, int x, int y, uint16_t color) const;
      int GetScreenWidth() const { return 84; }
      int GetScreenHeigt() const { return 48; }

    //protected:
      void initScreen();
      void clear() const;
      void display() const;

      void beginFrame() const {
        clear();
      }

      void endFrame() const {
        display();
      }
    };

  }
}
#endif