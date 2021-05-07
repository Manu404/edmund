#pragma once
#ifndef INPUTPROVIDER_INCLUDED
#define INPUTPROVIDER_INCLUDED

#include <memory>
#include "Arduino.h"
#include "mcp_provider.h"
#include "rotary.h"
#include "inputapi.h"

#define SERIAL_SPEED 115200

namespace Edmund {
  namespace Hardware {
    extern volatile bool rotaryInterruptTriggered; 

    class InputProvider : public IInputDevice
    {
    public:
      static std::shared_ptr<RotaryOnMcp> RotaryInstance;
      InputProvider() : IInputDevice::IInputDevice() { }
      InputProvider(std::unique_ptr<McpProvider> mcp, PinMapping mapping) : IInputDevice::IInputDevice(), mcpProvider(std::move(mcp)), pinMapping(mapping) { }
      ~InputProvider() {

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

      void initInputs();
      void beginFrame();
      void endFrame();

      ActivityStatus computeActivityStatus() const;
      ActivityStatus getActivityStatus() { return activityStatus; }

    private:
      int debugCombination = -1;
      double previousEncoderValue = 0, currentEncoderValue = 0;

      std::shared_ptr<McpProvider> mcpProvider;
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