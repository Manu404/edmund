#pragma once
#ifndef MCPPROVIDER_INCLUDED
#define MCPPROVIDER_INCLUDED

#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h>

namespace Edmund {
  namespace Hardware {
    class McpProvider {
      Adafruit_MCP23017* current_mcp;
      TwoWire* wire;
      int ready = 0;
    public:
      McpProvider() : current_mcp{ new Adafruit_MCP23017() }, wire{ new TwoWire() }  {  }
      void Initialize(byte SDA, byte SDB);
      int IsReady();
      void pinMode(byte pin, byte mode);
      void setupInterruptPinMode(byte pin, byte mode, byte interupt_mode);
      int digitalRead(byte pin);

      uint16_t GetRegisters() {
        if (!ready) return 0;
        return current_mcp->readGPIOAB();
      }
    };
  }
}
#endif