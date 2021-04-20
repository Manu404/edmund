/* based on https://github.com/buxtronix/arduino/tree/master/libraries/Rotary */

#ifndef rotary_h
#define rotary_h

#include "Arduino.h"
#include "mcp_provider.h"

#define ENABLE_PULLUPS  // Enable weak pullups

// Values returned by 'process'
#define DIR_NONE 0x0 // No complete step yet.
#define DIR_CW 0x10 // Clockwise step.
#define DIR_CCW 0x20 // Anti-clockwise step.

//#define HALF_STEP  // Enable this to emit codes twice per step.
#define R_START 0x0

#ifdef HALF_STEP
  // Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START}, // R_START (00)  
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START}, // R_CCW_BEGIN  
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START}, // R_CW_BEGIN  
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START}, // R_START_M (11)  
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW}, // R_CW_BEGIN_M  
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW}, // R_CCW_BEGIN_M
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START}, // R_START  
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW}, // R_CW_FINAL  
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START}, // R_CW_BEGIN  
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START}, // R_CW_NEXT 
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},  // R_CCW_BEGIN  
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW}, // R_CCW_FINAL  
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START}, // R_CCW_NEXT
};
#endif

namespace Edmund {
  namespace Hardware {
    class RotaryDecoder
    {
    public:
      RotaryDecoder() {
        state = R_START;
      }
    protected:
      unsigned char a;
      unsigned char b;
      virtual void refreshPinState() = 0;
      unsigned char getState() {
        refreshPinState();
        unsigned char pinstate = (a << 1) | b;
        state = ttable[state & 0xf][pinstate];
        return state & 0x30;
      }
    private:
      unsigned char state;
    };

    class RotaryOnMcp : RotaryDecoder
    {
    public:
      RotaryOnMcp(McpProvider* _provider, char _sda, char _sdb) : RotaryDecoder(), provider(_provider) {
        sda = _sda;
        sdb = _sdb;
      }
      int IsReady();
      double GetValue();
      double RefreshValue();
    private:
      McpProvider* provider;
      double current_value = 0;
      unsigned char sda;
      unsigned char sdb;
    protected:
      virtual void refreshPinState();
      double applyState(unsigned char state);
    };
  }
}
#endif