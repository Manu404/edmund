#pragma once
#ifndef INPUTPROVIDER_INCLUDED
#define INPUTPROVIDER_INCLUDED

#include <memory>
#include <list>
#include "Arduino.h"
#include "mcp_provider.h"
#include "rotary.h"
#include "input_api.h"
#include "input_control.h"
#include "input_reader.h"

#define SERIAL_SPEED 115200

namespace Edmund {
  namespace Hardware {
    extern volatile bool rotaryInterruptTriggered; 

    class InputDevice : public IInputDevice
    {
    public:
      static std::shared_ptr<RotaryOnMcp> RotaryInstance;
      InputDevice() : IInputDevice::IInputDevice() { }
      InputDevice(std::unique_ptr<McpProvider> mcp, PinMapping mapping) : IInputDevice::IInputDevice(), mcpProvider(std::move(mcp)), pinMapping(mapping) { 
      }
      ~InputDevice() {

      }
      
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

      void RegisterButton(std::unique_ptr<ButtonInputControl> button);

      void initInputs();
      void beginFrame();
      void endFrame();

      ActivityStatus computeActivityStatus() const;
      ActivityStatus getActivityStatus() { return activityStatus; }

    private:
      int debugCombination = -1;
      double previousEncoderValue = 0, currentEncoderValue = 0;

      std::shared_ptr<McpProvider> mcpProvider;
      std::list<std::unique_ptr<ButtonInputControl>> digitalInputs;
      PinMapping pinMapping;

      InputState current, previous, bounced;
      ActivityStatus activityStatus;

      void refreshInputs();
      float getPositionFromValue(float scale, int value) const;

      byte getButtonState(byte prev, byte curr) const;
      InputState readCurrentState();
      byte isPotActive() const;
    };
  }
}
#endif