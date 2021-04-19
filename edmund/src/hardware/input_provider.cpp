#include "./input_provider.h"

namespace Edmund {
  namespace Hardware {
    RotaryOnMcp* InputProvider::RotaryInstance;

    void OnRotaryInterupt() {
      RotaryOnMcp* current_rotary = Edmund::Hardware::InputProvider::RotaryInstance;
      if (!(current_rotary && current_rotary->IsReady())) return;
      current_rotary->RefreshValue();
    }

    void InputProvider::initInputs() {
      mcp_provider->Initialize(D5, D6);
      mcp_provider->setupInterruptPinMode(pinMapping.DT, INPUT, CHANGE);
      mcp_provider->setupInterruptPinMode(pinMapping.CLK, INPUT, CHANGE);

      pinMode(pinMapping.pot, INPUT);

      attachInterrupt(0, OnRotaryInterupt, CHANGE);
      Edmund::Hardware::InputProvider::RotaryInstance = new RotaryOnMcp(mcp_provider, pinMapping.DT, pinMapping.CLK);
    }

    void InputProvider::refreshInputs() {
      previous = current;
      current = getState();
    }

    // https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
    UIState InputProvider::getState() {

      current_encoder_value = Edmund::Hardware::InputProvider::RotaryInstance->GetValue();
      int direction = previous_encoder_value - current_encoder_value;
      previous_encoder_value = current_encoder_value;

      int middle = 0;
      float pot = analogRead(pinMapping.pot);
      int left = 0;
      int right = 0;

      return UIState
      {
        right,
        middle,
        left,
        pot,
        left * right,
        left * right * middle * (pot > 1020) * current.debug,
        direction
      };
    }

    int InputProvider::isPressed(int prev, int curr) {
      return (prev == curr) ? (prev > curr ? -1 : 1) : 0;
    }

    int InputProvider::IsEncoderTurnedRight() {
      return current.rotary_direction < 0;
    }

    int InputProvider::IsEncoderTurnedLeft() {
      return current.rotary_direction > 0;
    }

    int InputProvider::IsRightPressed() {
      return isPressed(previous.right, current.right) == -1;
    }

    int InputProvider::IsLeftPressed() {
      return isPressed(previous.left, current.left) == -1;
    }

    int InputProvider::IsMiddlePressed() {
      return isPressed(previous.middle, current.middle) == -1;
    }

    int InputProvider::IsDebugPressed() {
      return isPressed(previous.debug, current.debug) == -1;
    }

    int InputProvider::IsResetPressed() {
      return isPressed(previous.reset, current.reset) == -1;
    }

    int InputProvider::GetEncoderDelta() {
      return current.rotary_direction;
    }

    int InputProvider::HasPotChanged() {
      return previous.pot != current.pot;
    }

    float InputProvider::GetPositionFromPot(float scale) {
      // log, resistor biased +5 top
      return (1024 * exp(log(((float)current.pot / 1024)))) / (1024 / scale);
    }
  }
}