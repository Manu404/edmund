#include "rotary.h"

namespace Edmund {
  namespace Hardware {
    int RotaryOnMcp::IsReady() {
      return provider && provider->IsReady();
    }

    double RotaryOnMcp::GetValue() {
      return current_value;
    }

    double RotaryOnMcp::RefreshValue() {
      return applyState(getState());
    }

    double RotaryOnMcp::applyState(unsigned char state) {

      if (state == DIR_CW)
        current_value++;
      else if (state == DIR_CCW)
        current_value--;
      return current_value;
    }

    void RotaryOnMcp::refreshPinState() {
      if (provider && provider->IsReady())
      {
        a = provider->digitalRead(sda);
        b = provider->digitalRead(sdb);
      }
    }
  }
}