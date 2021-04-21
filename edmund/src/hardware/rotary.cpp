#include "rotary.h"

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
    RotaryDecoder::RotaryDecoder() {
      state = R_START;
    }

    unsigned char RotaryDecoder::getState() {
      refreshPinState();
      unsigned char pinstate = (a << 1) | b;
      state = ttable[state & 0xf][pinstate];
      Serial.println(pinstate);
      return state & 0x30;
    }

    int RotaryOnMcp::IsReady() {
      return provider && provider->IsReady();
    }

    double RotaryOnMcp::GetValue() {
      return current_value;
    }

    double RotaryOnMcp::RefreshValue() {
      return applyState(getState());
    }

    double RotaryOnMcp::applyState(unsigned char state) {
      if (state == DIR_CW)
        current_value++;
      else if (state == DIR_CCW)
        current_value--;
      return current_value;
    }

    void RotaryOnMcp::refreshPinState() {
      if (provider && provider->IsReady())
      {
        uint16_t reg = provider->GetRegisters();
        a = bitRead(reg, sda);
        b = bitRead(reg, sdb);
      }
    }
  }
}