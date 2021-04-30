#pragma once
#ifndef INPUTPROVIDER_INCLUDED
#define INPUTPROVIDER_INCLUDED

#include <memory>
#include "Arduino.h"
#include "mcp_provider.h"
#include "rotary.h"

#define SERIAL_SPEED 115200
#define GPB 8
#define GPA 0
#define POT_ACTIVE_SENSITIVITY 10
#define POT_ACTIVE_SCALE 1000

namespace Edmund {
  namespace Hardware {
    extern volatile bool rotaryInterruptTriggered; 

    enum InputStatus {
      INPUT_Inactive = 0,
      INPUT_Active = 1,
      INPUT_Disabled = 2,
      INPUT_Sleep = 4
    };

    struct PinMapping {
      byte right = GPB + 0;
      byte middle = GPB + 2;
      byte left = GPB + 1;
      byte pot = A0;
      byte CLK = GPA + 1;
      byte DT = GPA + 2;
      byte SW = GPA + 3;
    };

    struct InputState {
      byte right;
      byte middle;
      byte left;
      int pot;
      byte debug;
      byte reset;
      int encoder_delta;
      byte encoder_switch;
    };

    class InputProvider
    {
    public:
      static RotaryOnMcp* RotaryInstance;
      InputProvider(std::unique_ptr<McpProvider> mcp, PinMapping mapping) : mcp_provider(std::move(mcp)), pinMapping(mapping) { }
      ~InputProvider() { }
      bool IsRightPressed() const;
      bool IsLeftPressed() const;
      bool IsMiddlePressed() const;
      bool IsDebugPressed() const;
      bool IsResetPressed() const;
      bool IsEncoderTurnedRight() const;
      bool IsEncoderTurnedLeft() const;
      bool IsRotarySwitchPressed() const;
      bool HasPotChanged() const;
      float GetPositionFromPot(float scale) const;
      int GetEncoderDelta() const;

    protected:
      void initInputs();
      byte refreshInputStatus();
      void beginFrame();
      void endFrame();
      InputStatus getInputStatus() { return status; }

    private:
      int debug_combination = -1;
      double previous_encoder_value = 0, current_encoder_value = 0;

      std::shared_ptr<McpProvider> mcp_provider;
      PinMapping pinMapping;

      InputState current, previous, bounced;
      InputStatus status;

      void refreshInputs();
      float getPositionFromValue(float scale, int value) const;

      byte getButtonState(byte prev, byte curr) const;
      InputState readCurrentState();
      byte isPotActive() const;
    };
  }
}
#endif