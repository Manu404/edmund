#pragma once
#ifndef OUTPUTAPI_INCLUDED
#define OUTPUTAPI_INCLUDED

#include "Arduino.h"

#define TARGET_FPS 60
#define FRAME_DURATION_MS (1000 / TARGET_FPS)

namespace Edmund {
  namespace Hardware {

    #define BLACK 1 ///< Black pixel
    #define WHITE 0 ///< White pixel

    class IPCD8544Api {
      public:
        virtual ~IPCD8544Api() = default;
        virtual void begin() = 0;
        virtual void initDisplay() = 0;
        virtual void setRotation(byte v) = 0;
        virtual void setContrast(byte c) = 0;
        virtual void setBias(byte b) = 0;
        virtual void setClockDivider(byte d) = 0;
        virtual void print(String m) = 0;
        virtual void println(String m) = 0;
        virtual void drawChar(int16_t x, int16_t y, unsigned char c, int16_t fgcolor, int16_t bgcolor) = 0;
        virtual void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) = 0;
        virtual void drawNumericBitmap(int16_t x, int16_t y, int n, int16_t w, int16_t h, uint16_t color) = 0;
        virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
        virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
        virtual void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) = 0;
        virtual void setCursor(int16_t x, int16_t y) = 0;
        virtual void setTextColor(uint16_t c) = 0;
        virtual void clearDisplay() = 0;
        virtual void display() = 0;
        virtual void useSmallFont() = 0;
        virtual void useMonoBoldFont() = 0;
    };

    class IOutputDevice {
      public:
        virtual void Print(String m) const = 0; 
        virtual void Print(String m, int x, int y) const  = 0;
        virtual void PrintLine(String m) const  = 0;
        virtual void DrawSymbol(int x_pos, int y_pos, const uint8_t* logo) const  = 0;
        virtual void PrintNumberSmall(int x_pos, int y_pos, int value, uint16_t color, int length) const  = 0;
        virtual void DrawScreen(const uint8_t* screen) const  = 0;
        virtual void DrawBox(int x, int y, int w, int h, uint16_t color) const  = 0;
        virtual void DrawBorder(int x, int y, int w, int h, uint16_t color) const  = 0;
        virtual void DrawScreen(const uint8_t* logo, int x) const  = 0;
        virtual void DrawLogo(int x, int y, int w, int h, const uint8_t* logo) const  = 0;
        virtual void PrintNumberLarge(int x, int y, u_int value, uint16_t color, int length) const  = 0;
        virtual void PrintLineCentered(const String& buf, int x, int y, uint16_t color) const  = 0;
        virtual int GetScreenWidth() const = 0;
        virtual int GetScreenHeigt() const = 0;
 
        virtual void initScreen() = 0;
        virtual void clear() const = 0;
        virtual void display() const = 0;
        virtual void beginFrame() const = 0;
        virtual void endFrame() const = 0;
    };
  }
}
#endif