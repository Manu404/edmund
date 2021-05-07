#include "input_control.h"


namespace Edmund {
  namespace Hardware {

    void ButtonInputControl::Initialize(){
      inputReader->Initialize();
    }

    void ButtonInputControl::RefreshState(){
      previousState = currentState;
      currentState = inputReader->GetState();
    }

    
    void PotentiometerInputControl::Initialize(){
      inputReader->Initialize();
    }
    void PotentiometerInputControl::RefreshState(){
      previousState = state;
      state = inputReader->GetState();
    }

  }
}