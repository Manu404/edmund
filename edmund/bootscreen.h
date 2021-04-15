#ifndef BOOTSCREEN_INCLUDED
#define BOOTSCREEN_INCLUDED

#include "hardware.h"
#include "game.h"
#include "screen.h"

const unsigned char logo[] PROGMEM = {
    // 'logo, 84x48px
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x00, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff,
    0xf0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xe0,
    0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xfc, 0x00, 0x3f, 0xff,
    0xff, 0xf0, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff,
    0x00, 0x7f, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xf8, 0x0f,
    0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff,
    0xf8, 0x0f, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff,
    0x01, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xf8, 0x07, 0x81, 0xff, 0xff, 0xf0, 0xff,
    0xff, 0xf0, 0x20, 0x07, 0xf8, 0x07, 0xc0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x30, 0x07, 0xfc,
    0x07, 0xc0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xe0, 0x78, 0x03, 0xfe, 0x07, 0xe0, 0xff, 0xff, 0xf0,
    0xff, 0xff, 0xe0, 0xf8, 0x01, 0xfe, 0x03, 0xe0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc0, 0xf8, 0x00,
    0xfc, 0x03, 0xe0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc0, 0xf8, 0x00, 0xfc, 0x01, 0xe0, 0x7f, 0xff,
    0xf0, 0xff, 0xff, 0xc1, 0xf0, 0x00, 0xfc, 0x01, 0xf0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc1, 0xf0,
    0xc0, 0xfc, 0x01, 0xf0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc1, 0xf8, 0xc0, 0x64, 0x00, 0xf0, 0x7f,
    0xff, 0xf0, 0xff, 0xff, 0xc1, 0xe7, 0xe0, 0x03, 0x80, 0xf0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0x81,
    0xe3, 0xf0, 0x03, 0xc0, 0x70, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0x81, 0xe3, 0xf8, 0x07, 0xc0, 0x30,
    0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc1, 0xc3, 0xf8, 0x07, 0xe0, 0x30, 0x7f, 0xff, 0xf0, 0xff, 0xff,
    0xc1, 0xc7, 0xfc, 0x07, 0xe0, 0x10, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc1, 0xc7, 0xfc, 0x07, 0xf0,
    0x10, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xc1, 0x8f, 0xfc, 0x07, 0xf0, 0x10, 0x7f, 0xff, 0xf0, 0xff,
    0xff, 0xc1, 0x8f, 0xfe, 0x03, 0xf8, 0x18, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xe3, 0x1f, 0xfe, 0x03,
    0xf8, 0x08, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xe3, 0x1f, 0xff, 0x03, 0xf8, 0x0c, 0x7f, 0xff, 0xf0,
    0xff, 0xff, 0xe6, 0x1f, 0xff, 0x03, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf6, 0x0f, 0xff,
    0x03, 0xf8, 0x07, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf4, 0x0f, 0xff, 0x03, 0xf0, 0x03, 0xff, 0xff,
    0xf0, 0xff, 0xff, 0xf8, 0x07, 0xff, 0x03, 0xe0, 0x01, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf9, 0xff,
    0xff, 0x0f, 0xe7, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0x07, 0xff, 0x1f, 0xfc, 0x0f, 0xff,
    0xff, 0xf0, 0xff, 0xff, 0xfc, 0x03, 0xff, 0x3f, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe,
    0x00, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xc0, 0x1f,
    0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff,
    0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01,
    0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xf0, 0xff,
    0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00,
    0x3f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0
};

// 'blue', 9x10px
const unsigned char symbol1 [] PROGMEM = {
 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x3e, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x7b, 0x00, 0x7f, 0x00, 
  0x3e, 0x00, 0x00, 0x00
};
// 'forest', 9x10px
const unsigned char symbol2 [] PROGMEM = {
  0x00, 0x00, 0x3e, 0x00, 0x77, 0x00, 0x5d, 0x00, 0x6b, 0x00, 0x7f, 0x00, 0x5d, 0x00, 0x08, 0x00, 
  0x3e, 0x00, 0x00, 0x00
};
// 'mountain', 9x10px
const unsigned char symbol3 [] PROGMEM = {
  0x00, 0x00, 0x17, 0x00, 0x02, 0x00, 0x41, 0x00, 0x31, 0x00, 0x7b, 0x00, 0x5f, 0x00, 0x6f, 0x00, 
  0x3e, 0x00, 0x00, 0x00
};
// 'plain', 9x10px
const unsigned char symbol4 [] PROGMEM = {
  0x00, 0x00, 0x11, 0x00, 0x0a, 0x00, 0x3c, 0x00, 0x55, 0x00, 0x1e, 0x00, 0x34, 0x00, 0x52, 0x00, 
  0x08, 0x00, 0x00, 0x00
};
// 'swamp', 9x10px
const unsigned char symbol5 [] PROGMEM = {
  0x00, 0x00, 0x3e, 0x00, 0x7f, 0x00, 0x49, 0x00, 0x7f, 0x00, 0x36, 0x00, 0x2a, 0x00, 0x3e, 0x00, 
  0x2a, 0x00, 0x00, 0x00
};


class BootScreen : public IScreen
{
  private:
    int tick = 0; 
    int symbol = 0;
    
    
  public: 
    BootScreen (){
      
    }
    virtual ScreenEnum loop(Hardware& hardware, Game& game)
    {
      if(tick == 20) tick = 0;
      
      tick += 1;
      hardware.DrawScreen(logo);
        
      if (hardware.IsMiddlePressed() == 1 || tick == 20)
        return MainScreenEnum;
      return BootScreenEnum;
    } 
};

#endif
