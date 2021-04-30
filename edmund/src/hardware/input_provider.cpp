#include "./input_provider.h"

namespace Edmund {
  namespace Hardware {
    RotaryOnMcp* InputProvider::RotaryInstance;

    volatile bool rotaryInterruptTriggered = false;

    void ICACHE_RAM_ATTR OnRotaryInterupt() {
      if(!rotaryInterruptTriggered) rotaryInterruptTriggered = true;
      Serial.print('.');
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

      pinMode(pinMapping.pot, INPUT_PULLUP);

      Edmund::Hardware::InputProvider::RotaryInstance = new RotaryOnMcp(mcp_provider, pinMapping.DT, pinMapping.CLK);
      attachInterrupt(D7, OnRotaryInterupt, CHANGE);
    }

    void InputProvider::beginFrame() {
      refreshInputs();
    }

    void InputProvider::endFrame() {
      refreshInputStatus();
      previous = current;
    }

    void InputProvider::refreshInputs() {  
      current = readCurrentState();
    }

    InputState InputProvider::readCurrentState() {

      current_encoder_value = Edmund::Hardware::InputProvider::RotaryInstance->GetValue();
      int encoder_delta = previous_encoder_value - current_encoder_value;
      previous_encoder_value = current_encoder_value;

      byte encoder_switch = mcp_provider->digitalRead(pinMapping.SW);
      byte middle = mcp_provider->digitalRead(pinMapping.middle);
      byte left = mcp_provider->digitalRead(pinMapping.left);
      byte right = mcp_provider->digitalRead(pinMapping.right);

      // dummy workaround ~ issue related to breadboard
      bounced.middle = middle > 0 ? bounced.middle + 1 : 0;
      bounced.left = left > 0 ? bounced.left + 1 : 0;
      bounced.right = right > 0 ? bounced.right + 1 : 0;

      int pot = analogRead(pinMapping.pot);

      return InputState
      {
        bounced.right > 3,
        bounced.middle > 3,
        bounced.left > 3,
        pot,
        (byte)(left * right),
        (byte)(left * right * middle * (pot > 1020) * current.debug),
        encoder_delta,
        encoder_switch
      };
    }

    byte InputProvider::refreshInputStatus() {
      int computedStatus = (previous.encoder_delta != current.encoder_delta ||
        isPotActive() ||
        previous.middle != current.middle ||
        previous.left != current.left ||
        previous.right != current.right ||
        previous.encoder_switch != current.encoder_switch); // + isDisabled;
      status = (InputStatus)(computedStatus);
    }

    byte InputProvider::getButtonState(byte prev, byte curr) const {
      return (prev != curr) ? (prev > curr ? 1 : 2) : 0;
    }

    bool InputProvider::IsEncoderTurnedRight() const {
      return current.encoder_delta < 0;
    }

    bool InputProvider::IsEncoderTurnedLeft() const {
      return current.encoder_delta > 0;
    }

    bool InputProvider::IsRightPressed() const {
      return getButtonState(previous.right, current.right) == 1;
    }

    bool InputProvider::IsLeftPressed() const {
      return getButtonState(previous.left, current.left) == 1;
    }

    bool InputProvider::IsMiddlePressed() const {
      return getButtonState(previous.middle, current.middle) == 1;
    }

    bool InputProvider::IsRotarySwitchPressed() const {
      return previous.encoder_switch > current.encoder_switch;
    }

    bool InputProvider::IsDebugPressed() const {
      return getButtonState(previous.debug, current.debug) == 1;
    }

    bool InputProvider::IsResetPressed() const {
      return getButtonState(previous.reset, current.reset) == 1;
    }

    int InputProvider::GetEncoderDelta() const {
      return current.encoder_delta;
    }

    bool InputProvider::HasPotChanged() const {
      return previous.pot != current.pot;
    }

    float InputProvider::GetPositionFromPot(float scale) const {
      return getPositionFromValue(scale, current.pot);
    }

    float InputProvider::getPositionFromValue(float scale, int value) const {
      if (scale == 0) return 0;
      // log, resistor biased +5 top
      return (1024 * exp(log(((float)value / 1024)))) / (1024 / scale);
    }

    byte InputProvider::isPotActive() const {
      return abs(getPositionFromValue(POT_ACTIVE_SCALE, previous.pot) - getPositionFromValue(POT_ACTIVE_SCALE, current.pot)) > POT_ACTIVE_SENSITIVITY;
    }

  }
}