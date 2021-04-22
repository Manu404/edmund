#pragma once
#ifndef INPUTPROVIDER_INCLUDED
#define INPUTPROVIDER_INCLUDED

#include "rotary.h"

#define SERIAL_SPEED 115200
#define GPB 8
#define GPA 0

namespace Edmund {
  namespace Hardware {
    struct PinMapping {
      byte right = GPB + 0;
      byte middle = GPB + 2;
      byte left = GPB + 1;
      int pot = A0;
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
      int rotary_direction;
      byte rotary_switch;
    };

    class InputProvider
    {
    public:
      static RotaryOnMcp* RotaryInstance;
      InputProvider(McpProvider* mcp, PinMapping mapping) : mcp_provider(mcp), pinMapping(mapping) { }
      int IsRightPressed();
      int IsLeftPressed();
      int GetEncoderDelta();
      int IsMiddlePressed();
      int IsDebugPressed();
      int IsResetPressed();
      int IsEncoderTurnedRight();
      int IsEncoderTurnedLeft();
      int IsRotarySwitchPressed();
      int HasPotChanged();
      float GetPositionFromPot(float scale);

    protected:
      void initInputs();
      void refreshInputs();

    private:
      PinMapping pinMapping;
      McpProvider* mcp_provider;

      InputState current, previous;
      int debug_combination = -1;
      double previous_encoder_value = 0, current_encoder_value = 0;

      int isPressed(int prev, int curr);
      InputState getState();
    };
  }
}
#endif