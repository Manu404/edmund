#pragma once
#ifndef INNPUTCONTROL_INCLUDED
#define INNPUTCONTROL_INCLUDED

#include "Arduino.h"
#include <memory>
#include "mcp_provider.h"
#include "input_api.h"

namespace Edmund {
  namespace Hardware {

    // template <typename T>
    // class DefaultInputControlWithStateMemory : public IInputControl<T> {
    //   private:
    //     std::unique_ptr<IInputReader<T>> inputReader;
    //     T state, previousState;
    //   public:
    //     DefaultInputControlWithStateMemory(std::unique_ptr<IInputReader<T>> _digitalReader): inputReader(std::move(_digitalReader)) { }

    //     void Initialize(){
    //       inputReader->Initialize();
    //     }
    //     void RefreshState(){
    //       previousState = state;
    //       state = inputReader->GetValue();
    //     }
    //     template <typename T>
    //     T GetState(){
    //       return state;
    //     }
    //     bool HasChanged(){
    //       return state != previousState;
    //     }
    // };

    class ButtonInputControl : public IInputControl<byte> {
      private:
        std::unique_ptr<IInputReader<byte>> inputReader;
      public:
        ButtonInputControl(std::unique_ptr<IInputReader<byte>> _digitalReader): inputReader(std::move(_digitalReader)) { }
        void Initialize();
        void RefreshState();
    };

    class PotentiometerInputControl : public IInputControl<float> {
      private:
        std::unique_ptr<IInputReader<float>> inputReader;
        float state = 0, previousState;
      public:
        PotentiometerInputControl(std::unique_ptr<IInputReader<float>> _digitalReader): inputReader(std::move(_digitalReader)) { }
        void Initialize();
        void RefreshState();
    };
  }
}
#endif