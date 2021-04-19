#include "mcp_provider.h"

namespace Edmund {
  namespace Hardware {
    void McpProvider::Initialize(uint SDA, uint SDB) {
      Serial.println(String(SDA) + " - " + String(SDB));
      wire->begin(SDA, SDB);
      current_mcp->begin(wire);
      current_mcp->setupInterrupts(true, false, LOW);
      ready = 1;
    }

    int McpProvider::IsReady() {
      return ready;
    }

    void McpProvider::pinMode(int pin, int mode) {
      current_mcp->pinMode(pin, mode);
    }
    void McpProvider::setupInterruptPinMode(uint pin, int mode, int interupt_mode) {
      current_mcp->pinMode(pin, mode);
      current_mcp->pinMode(pin, interupt_mode);
    }
    int McpProvider::digitalRead(int pin) {
      return current_mcp->digitalRead(pin);
    }
  }
}