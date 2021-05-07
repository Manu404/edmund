/* based on https://github.com/buxtronix/arduino/tree/master/libraries/Rotary */

#ifndef rotary_h
#define rotary_h

#include "Arduino.h"
#include "mcp_provider.h"

#include <memory>

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
        virtual ~RotaryDecoder() { }
      protected:
        byte sdaState;
        byte sdbState;
        virtual void refreshPinState() = 0;
        byte getState();
      private:
        byte state;
    };

    class RotaryOnMcp : RotaryDecoder
    {
      private:
        double currentValue = 0;
        byte sda;
        byte sdb;
        std::shared_ptr<McpProvider> provider;
      public:
        RotaryOnMcp(std::shared_ptr<McpProvider> _provider, byte _sda, byte _sdb) : RotaryDecoder() {
          sda = _sda;
          sdb = _sdb;
          provider = _provider;
        }
        int IsReady() const;
        double GetValue() const;
        double RefreshValue();
      protected:
        virtual void refreshPinState() override;
        double applyState(byte state);
    };
  }
}
#endif