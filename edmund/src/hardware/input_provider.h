#pragma once
#ifndef INPUTPROVIDER_INCLUDED
#define INPUTPROVIDER_INCLUDED

#include "rotary.h"

#define SERIAL_SPEED 115200
namespace Edmund {
  namespace Hardware {
    struct PinMapping {
      int right = 1;
      int middle = 3;
      int left = 2;
      int pot = A0;
      int CLK = 1;
      int DT = 2;
    };

    struct UIState {
      int right;
      int middle;
      int left;
      int pot;
      int debug;
      int reset;
      int rotary_direction;
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
      int HasPotChanged();
      float GetPositionFromPot(float scale);

    protected:
      void initInputs();
      void refreshInputs();

    private:
      PinMapping pinMapping;
      McpProvider* mcp_provider;

      UIState current, previous;
      int debug_combination = -1;
      int previous_encoder_value = 0, current_encoder_value = 0;

      int isPressed(int prev, int curr);
      UIState getState();
    };
  }
}
#endif