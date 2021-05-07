#pragma once
#ifndef LCDPROVIDER_INCLUDED
#define LCDPROVIDER_INCLUDED

#include "output_api.h"

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
      PCD8544OutputDevice() { }
      PCD8544OutputDevice(std::unique_ptr<IPCD8544Api> _lcd) 
        : IOutputDevice::IOutputDevice(), lcd(std::move(_lcd)) 
      { }

      void Print(String m) const; 
      void Print(String m, int x, int y) const;
      void PrintLine(String m) const;
      void DrawSymbol(int x, int y, const uint8_t* logo) const;
      void DrawScreen(const uint8_t* screen) const;
      void DrawBox(int x, int y, int w, int h, uint16_t color) const;
      void DrawBorder(int x, int y, int w, int h, uint16_t color) const;
      void DrawScreen(const uint8_t* logo, int x) const;
      void DrawLogo(int x, int y, int w, int h, const uint8_t* logo) const;
      void PrintLineCentered(const String& buf, int x, int y, uint16_t color) const;
      void PrintNumberSmall(int x, int y, int value, uint16_t color, int minLength) const;
      void PrintNumberLarge(int x, int y, int value, uint16_t color, int minLength) const;
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