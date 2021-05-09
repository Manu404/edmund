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
  
    //
    // IInputReader represent the lowest layer of input handling, it's "hardware api" level, you'll find digitalRead or pinMode called here. 
    // This encapsulate logic regarding "the connnection point" between our code and the phisical device, without any opinion about what is really connected behind. 
    // It yield the real actual input value every time GetState() is called. It's the "pin" or the "wire".
    //    It's the layer to substitute during end-to-end integration test using input scenarios.
    //    It's the layer to update/extend when hardware api change.
    //    It's the layer to extend when porting to new hardware, regarding input handling.
    //    eg: I wannt to run on a aspberry pi with a totally different api, considering the rest of our electronic didn't changed (or not radically),
    //        I'll certainly just have to write a set of IInputReader to get access to the gpio of the pi, the higher level logic will not have to be touched.
    //        Initialized is called once during setup. GetState() is called once per frame during runtime and call readState(). readState() should be implemented to call the current api.
    // NOTE: I would keep the return types really simple here. Byte is often used instead of bool to allow for non binary state, even if not used yet, that intent should be expressed imho.
    //       Typically, digital and analog IO would represent the vast majority of written readers, meaning bool for digital and uint32 for analog should be most of the return types. (really nice adc btw)
    //
    // input_reader.h for self-explainatory examples
    //
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

    //
    // IInputControl represent a logical layer on top of the input reader that encapsulate interaction logic for the associated input. 
    // It rely on a IInputReader, even tho it is not enforced. This encapsulate logic regarding the connected input component. 
    // State is refreshed once per frame through RefreshState(), the main method to implement, an exposed through GetState().
    //    eg: a button, a potentiometer, a button with state memory logic, a photosensor, a current-to-voltage converter
    //    It's the layer to extend when implementing new input logic around a hardware inputs.
    //    It's the layer to change when
    //    eg: there's a logarithmic pot implementation, and I want to use a linear pot.
    //        I'll implemennt an IInputControl that encpasulate the mapping logic between the actual value read from the low level through an IInputReader
    //        and the ranged value expected from the control. (for instance, a range between 1-10 on a logarithmic scale)
    //
    // input_control.h to see self explaatory implementations.
    //
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

    enum ActivityStatus {
      INPUT_Inactive = 0,
      INPUT_Active = 1,
      INPUT_Disabled = 2,
      INPUT_Sleep = 4
    };

    //
    // IInputDevice represent the composition of IInputControl and is consumed by the screens. 
    // It acts as a facade for the IInputControl collection by providing high level input state querying.
    //    It's the layer to change when new input need to be exposed to screens
    //
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

  }
}
#endif