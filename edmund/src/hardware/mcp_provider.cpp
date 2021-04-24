#include "mcp_provider.h"

namespace Edmund {
  namespace Hardware {

    void McpProvider::Initialize(byte SDA, byte SDB) {
      wire->begin(SDA, SDB);
      wire->setClock(800000);
      current_mcp->begin(wire);
      current_mcp->readGPIOAB();
      current_mcp->setupInterrupts(true, false, LOW);
      ready = 1;
    }

    int McpProvider::IsReady() {
      return ready;
    }

    void McpProvider::pinMode(byte pin, byte mode) {
      current_mcp->pinMode(pin, mode);
    }
    void McpProvider::setupInterruptPinMode(byte pin, byte mode, byte interupt_mode) {
      current_mcp->pinMode(pin, mode);
      current_mcp->setupInterruptPin(pin, interupt_mode);
    }
    int McpProvider::digitalRead(byte pin) {
      if (!ready) return 0;
      return current_mcp->digitalRead(pin);
    }
  }
}