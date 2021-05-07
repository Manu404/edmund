#pragma once
#ifndef INNPUTAPI_INCLUDED
#define INNPUTAPI_INCLUDED

#include "Arduino.h"

#define GPB 8
#define GPA 0
#define POT_ACTIVE_SENSITIVITY 10
#define POT_ACTIVE_SCALE 1000

namespace Edmund {
  namespace Hardware {

    enum ActivityStatus {
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
      int encoderDelta;
      byte encoderSwitch;
    };

    template <typename T>
    class IInputControl {
      protected:
        T currentState, previousState;
      public:        
        IInputControl() = default;
        virtual ~IInputControl() = default;
        virtual void Initialize() = 0;
        virtual void RefreshState() = 0;

        T GetState() { 
          return currentState; 
        };
        bool HasChanged(){
          return currentState != previousState;
        };
    };

    template <typename T>
    class IInputReader {
      protected:
        virtual void readState() = 0;
        T state;
      public:
        IInputReader() = default;
        virtual ~IInputReader() = default;
        virtual void Initialize() = 0;
        T GetState() { 
          readState();
          return state; 
        };
    };

    class IInputDevice {
      public:
        IInputDevice() = default;
        virtual ~IInputDevice() = default;

        virtual bool IsRightPressed() const = 0;
        virtual bool IsLeftPressed() const = 0;
        virtual bool IsMiddlePressed() const = 0;
        virtual bool IsDebugPressed() const = 0;
        virtual bool IsResetPressed() const = 0;
        virtual bool IsEncoderTurnedRight() const = 0;
        virtual bool IsEncoderTurnedLeft() const = 0;
        virtual bool IsRotarySwitchPressed() const = 0;
        virtual bool HasPotChanged() const = 0;
        virtual float GetPositionFromPot(float scale) const = 0;
        virtual int GetEncoderDelta() const = 0;
        virtual void initInputs() = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual ActivityStatus getActivityStatus() = 0;
    };
  }
}
#endif