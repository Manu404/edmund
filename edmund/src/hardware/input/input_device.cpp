#include "input_device.h"

namespace Edmund {
  namespace Hardware {
    // 
    // on interrupt D7
    //
    std::shared_ptr<RotaryOnMcp> InputDevice::RotaryInstance;
    volatile bool rotaryInterruptTriggered = false;
    void ICACHE_RAM_ATTR OnRotaryInterupt() {
      if(!rotaryInterruptTriggered) rotaryInterruptTriggered = true;
      Serial.print('.');
      std::shared_ptr<RotaryOnMcp> current_rotary = Edmund::Hardware::InputDevice::RotaryInstance;
      if (current_rotary && current_rotary->IsReady()) 
        current_rotary->RefreshValue();
    }

    void InputDevice::initInputs() {
      mcpProvider->Initialize(D5, D6);
      mcpProvider->setupInterruptPinMode(pinMapping.DT, INPUT, CHANGE);
      mcpProvider->setupInterruptPinMode(pinMapping.CLK, INPUT, CHANGE);

      // mcpProvider->pinMode(pinMapping.left, INPUT);
      // mcpProvider->pinMode(pinMapping.middle, INPUT);
      // mcpProvider->pinMode(pinMapping.right, INPUT);

      pinMode(pinMapping.pot, INPUT_PULLUP);

      Edmund::Hardware::InputDevice::RotaryInstance = std::shared_ptr<RotaryOnMcp>(new RotaryOnMcp(mcpProvider, pinMapping.DT, pinMapping.CLK));
      attachInterrupt(D7, OnRotaryInterupt, CHANGE);

      digitalInputs.push_back(
        std::unique_ptr<ButtonInputControl>(new ButtonInputControl(
          std::unique_ptr<MCPDigitalInputReader>(new MCPDigitalInputReader(pinMapping.left, mcpProvider))
          )
        )
      );
      digitalInputs.push_back(
        std::unique_ptr<ButtonInputControl>(new ButtonInputControl(
          std::unique_ptr<MCPDigitalInputReader>(new MCPDigitalInputReader(pinMapping.middle, mcpProvider))
          )
        )
      );
      digitalInputs.push_back(
        std::unique_ptr<ButtonInputControl>(new ButtonInputControl(
          std::unique_ptr<MCPDigitalInputReader>(new MCPDigitalInputReader(pinMapping.right, mcpProvider))
          )
        )
      );

      for(auto const& in : digitalInputs)
          in->Initialize();
    }
    
    void InputDevice::RegisterButton(std::unique_ptr<ButtonInputControl> button){
      digitalInputs.push_back(std::move(button));
    }

    void InputDevice::beginFrame() {
      refreshInputs();
      activityStatus = computeActivityStatus();
    }

    void InputDevice::endFrame() {
      previous = current;
    }

    void InputDevice::refreshInputs() {  
      current = readCurrentState();
    }

    InputState InputDevice::readCurrentState() {

      currentEncoderValue = Edmund::Hardware::InputDevice::RotaryInstance->GetValue();
      int encoder_delta = previousEncoderValue - currentEncoderValue;
      previousEncoderValue = currentEncoderValue;

      byte encoder_switch = mcpProvider->digitalRead(pinMapping.SW);
      byte middle = mcpProvider->digitalRead(pinMapping.middle);
      byte left = mcpProvider->digitalRead(pinMapping.left);
      byte right = mcpProvider->digitalRead(pinMapping.right);

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

    ActivityStatus InputDevice::computeActivityStatus() const {
      int computedStatus = (previous.encoderDelta != current.encoderDelta ||
        isPotActive() ||
        previous.middle != current.middle ||
        previous.left != current.left ||
        previous.right != current.right ||
        previous.encoderSwitch != current.encoderSwitch); // + isDisabled;
      return (ActivityStatus)(computedStatus);
    }

    byte InputDevice::getButtonState(byte prev, byte curr) const {
      return (prev != curr) ? (prev > curr ? 1 : 2) : 0;
    }

    bool InputDevice::IsEncoderTurnedRight() const {
      return current.encoderDelta < 0;
    }

    bool InputDevice::IsEncoderTurnedLeft() const {
      return current.encoderDelta > 0;
    }

    bool InputDevice::IsRightPressed() const {
      return getButtonState(previous.right, current.right) == 1;
    }

    bool InputDevice::IsLeftPressed() const {
      return getButtonState(previous.left, current.left) == 1;
    }

    bool InputDevice::IsMiddlePressed() const {
      return getButtonState(previous.middle, current.middle) == 1;
    }

    bool InputDevice::IsRotarySwitchPressed() const {
      return previous.encoderSwitch > current.encoderSwitch;
    }

    bool InputDevice::IsDebugPressed() const {
      return getButtonState(previous.debug, current.debug) == 1;
    }

    bool InputDevice::IsResetPressed() const {
      return getButtonState(previous.reset, current.reset) == 1;
    }

    int InputDevice::GetEncoderDelta() const {
      return current.encoderDelta;
    }

    bool InputDevice::HasPotChanged() const {
      return previous.pot != current.pot;
    }

    float InputDevice::GetPositionFromPot(float scale) const {
      return getPositionFromValue(scale, current.pot);
    }

    float InputDevice::getPositionFromValue(float scale, int value) const {
      if (scale == 0) return 0;
      // log, resistor biased +5 top
      return (1024 * exp(log(((float)value / 1024)))) / (1024 / scale);
    }

    byte InputDevice::isPotActive() const {
      return abs(getPositionFromValue(POT_ACTIVE_SCALE, previous.pot) - getPositionFromValue(POT_ACTIVE_SCALE, current.pot)) > POT_ACTIVE_SENSITIVITY;
    }

  }
}