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

namespace Edmund {
  namespace Hardware {
    class RotaryDecoder
    {
      public:
        RotaryDecoder();
      protected:
        byte sda_state;
        byte sdb_state;
        virtual void refreshPinState() = 0;
        byte getState();
      private:
        byte state;
    };

    class RotaryOnMcp : RotaryDecoder
    {
      public:
        RotaryOnMcp(McpProvider* _provider, byte _sda, byte _sdb) : RotaryDecoder(), provider(_provider) {
          sda = _sda;
          sdb = _sdb;
        }
        int IsReady();
        double GetValue();
        double RefreshValue();
      private:
        McpProvider* provider;
        double current_value = 0;
        byte sda;
        byte sdb;
      protected:
        virtual void refreshPinState();
        double applyState(byte state);
    };
  }
}
#endif