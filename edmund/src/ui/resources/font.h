#ifndef _font_h
#define _font_h

// https://glenviewsoftware.com/projects/products/adafonteditor/adafruit-gfx-font-format/
#include <Adafruit_GFX.h>

namespace Edmund {
  namespace UI {
    namespace Resources {

      // http://javl.github.io/image2cpp/
      const unsigned char numericFont[][5] PROGMEM = {
        // 'numeric_0, 4x5px
        { 0x20, 0x50, 0x50, 0x50, 0x20 },
        // 'numeric_1, 4x5px
        { 0x20, 0x60, 0x20, 0x20, 0x70 },
        // 'numeric_2, 4x5px
        { 0x70, 0x10, 0x70, 0x40, 0x70 },
        // 'numeric_3, 4x5px
        { 0x70, 0x10, 0x30, 0x10, 0x70 },
        // 'numeric_4, 4x5px
        { 0x10, 0x30, 0x50, 0x70, 0x10 },
        // 'numeric_5, 4x5px
        { 0x70, 0x40, 0x70, 0x10, 0x70 },
        // 'numeric_6, 4x5px
        { 0x70, 0x40, 0x70, 0x50, 0x70 },
        // 'numeric_7, 4x5px
        { 0x70, 0x10, 0x20, 0x20, 0x20 },
        // 'numeric_8, 4x5px
        { 0x70, 0x50, 0x70, 0x50, 0x70 },
        // 'numeric_9, 4x5px
        { 0x70, 0x50, 0x70, 0x10, 0x10 }
      };

      const unsigned char numericFontBitmap[] PROGMEM = {
        // 'numeric_0, 4x5px
        0x20, 0x50, 0x50, 0x50, 0x20,
        // 'numeric_1, 4x5px
        0x20, 0x60, 0x20, 0x20, 0x70,
        // 'numeric_2, 4x5px
        0x70, 0x10, 0x70, 0x40, 0x70,
        // 'numeric_3, 4x5px
        0x70, 0x10, 0x30, 0x10, 0x70,
        // 'numeric_4, 4x5px
        0x10, 0x30, 0x50, 0x70, 0x10,
        // 'numeric_5, 4x5px
        0x70, 0x40, 0x70, 0x10, 0x70,
        // 'numeric_6, 4x5px
        0x70, 0x40, 0x70, 0x50, 0x70,
        // 'numeric_7, 4x5px
        0x70, 0x10, 0x20, 0x20, 0x20,
        // 'numeric_8, 4x5px
        0x70, 0x50, 0x70, 0x50, 0x70,
        // 'numeric_9, 4x5px
        0x70, 0x50, 0x70, 0x10, 0x10
      };


      const GFXglyph numericFontGlyphs[] PROGMEM = {
        { 0, 4, 5, 0, 0, 0 },// 'numeric_0'
        { 4, 4, 5, 0, 0, 0 },// 'numeric_1'
        { 8, 4, 5, 0, 0, 0 },// 'numeric_2'
        { 12, 4, 5, 0, 0, 0},// 'numeric_3'
        { 16, 4, 5, 0, 0, 0},// 'numeric_4'
        { 20, 4, 5, 0, 0, 0},// 'numeric_5'
        { 24, 4, 5, 0, 0, 0},// 'numeric_6'
        { 28, 4, 5, 0, 0, 0},// 'numeric_7'
        { 32, 4, 5, 0, 0, 0},// 'numeric_8'
        { 36, 4, 5, 0, 0, 0}// 'numeric_9'
      };

      const GFXfont  numericFontGFX PROGMEM = {
        (uint8_t*)numericFontBitmap,
        (GFXglyph*)numericFontGlyphs,
        48, 57, 7
      };
    }
  }
}

#endif

