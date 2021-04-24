#include "./input_provider.h"

namespace Edmund {
  namespace Hardware {
    RotaryOnMcp* InputProvider::RotaryInstance;

    volatile bool interrupt = false;

    void ICACHE_RAM_ATTR OnRotaryInterupt() {
      interrupt = true;
      Serial.println('.');
      RotaryOnMcp* current_rotary = Edmund::Hardware::InputProvider::RotaryInstance;
      if (!(current_rotary && current_rotary->IsReady())) return;
      current_rotary->RefreshValue();
    }

    void InputProvider::initInputs() {
      mcp_provider->Initialize(D5, D6);
      mcp_provider->setupInterruptPinMode(pinMapping.DT, INPUT, CHANGE);
      mcp_provider->setupInterruptPinMode(pinMapping.CLK, INPUT, CHANGE);

      mcp_provider->pinMode(pinMapping.left, INPUT);
      mcp_provider->pinMode(pinMapping.middle, INPUT);
      mcp_provider->pinMode(pinMapping.right, INPUT);

      pinMode(pinMapping.pot, INPUT);

      Edmund::Hardware::InputProvider::RotaryInstance = new RotaryOnMcp(mcp_provider, pinMapping.DT, pinMapping.CLK);
      attachInterrupt(D7, OnRotaryInterupt, CHANGE);
    }

    void InputProvider::refreshInputs() {      
      current = getState();
    }

    void InputProvider::updateInputs() {
      previous = current;
    }

    // https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
    InputState InputProvider::getState() {
      current_encoder_value = Edmund::Hardware::InputProvider::RotaryInstance->GetValue();
      int direction = previous_encoder_value - current_encoder_value;
      previous_encoder_value = current_encoder_value;

      byte rotary_switch = mcp_provider->digitalRead(pinMapping.SW);
      byte middle = mcp_provider->digitalRead(pinMapping.middle);
      byte left = mcp_provider->digitalRead(pinMapping.left);
      byte right = mcp_provider->digitalRead(pinMapping.right);

      //byte rotary_switch = 0, middle = 0, left = 0, right = 0;

      // dummy workaround ~ issue related to breadboard
      bounced.middle = middle > 0 ? bounced.middle + 1 : 0;
      bounced.left = left > 0 ? bounced.middle + 1 : 0;
      bounced.right = right > 0 ? bounced.middle + 1 : 0;

      int pot = analogRead(pinMapping.pot);

      return InputState
      {
        bounced.right > 3,
        bounced.middle > 3,
        bounced.left > 3,
        pot,
        (byte)(left * right),
        (byte)(left * right * middle * (pot > 1020) * current.debug),
        direction,
        rotary_switch
      };
    }

    int InputProvider::isPressed(int prev, int curr) {
      return (prev != curr) ? (prev > curr ? 1 : -1) : 0;
    }

    int InputProvider::IsEncoderTurnedRight() {
      return current.rotary_direction < 0;
    }

    int InputProvider::IsEncoderTurnedLeft() {
      return current.rotary_direction > 0;
    }

    int InputProvider::IsRightPressed() {
      return isPressed(previous.right, current.right) == 1;
    }

    int InputProvider::IsLeftPressed() {
      return isPressed(previous.left, current.left) == 1;
    }

    int InputProvider::IsMiddlePressed() {
      return isPressed(previous.middle, current.middle) == 1;
    }

    int InputProvider::IsRotarySwitchPressed() {
      return previous.rotary_switch > current.rotary_switch;
    }

    int InputProvider::IsDebugPressed() {
      return isPressed(previous.debug, current.debug) == 1;
    }

    int InputProvider::IsResetPressed() {
      return isPressed(previous.reset, current.reset) == 1;
    }

    int InputProvider::GetEncoderDelta() {
      return current.rotary_direction;
    }

    int InputProvider::HasPotChanged() {
      return previous.pot != current.pot;
    }

    float InputProvider::GetPositionFromPot(float scale) {
      if (scale == 0) return 0;
      // log, resistor biased +5 top
      return (1024 * exp(log(((float)current.pot / 1024)))) / (1024 / scale);
    }

    byte InputProvider::IsActive(){
      return  previous.rotary_direction != current.rotary_direction ||
        (abs(previous.pot - current.pot) > 50)||
        previous.middle != current.middle ||
        previous.left != current.left ||
        previous.right != current.right ||
        previous.rotary_switch != current.rotary_switch;
    }
  }
}