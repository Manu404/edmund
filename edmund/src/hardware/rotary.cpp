#include "rotary.h"

int RotaryOnMcp::IsReady() {
  return provider && provider->IsReady();
}

int RotaryOnMcp::GetValue() {
  return current_value;
}

int RotaryOnMcp::RefreshValue() {
  return applyState(getState());
}

unsigned char RotaryOnMcp::applyState(unsigned char state) {
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
