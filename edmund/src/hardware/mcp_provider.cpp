#include "mcp_provider.h"

namespace Edmund {
  namespace Hardware {

    void McpProvider::Initialize(byte SDA, byte SDB) {
      wire->begin(SDA, SDB);
      wire->setClock(800000);
      currentMcp->begin(wire);
      currentMcp->readGPIOAB();
      currentMcp->setupInterrupts(true, false, LOW);
      ready = 1;
    }

    bool McpProvider::IsReady() const {
      return ready;
    }

    void McpProvider::pinMode(byte pin, byte mode) {
      currentMcp->pinMode(pin, mode);
    }
    void McpProvider::setupInterruptPinMode(byte pin, byte mode, byte interupt_mode) {
      currentMcp->pinMode(pin, mode);
      currentMcp->setupInterruptPin(pin, interupt_mode);
    }
    int McpProvider::digitalRead(byte pin) {
      if (!ready) return 0;
      return currentMcp->digitalRead(pin);
    }
  }
}