#pragma once
#ifndef MCPPROVIDER_INCLUDED
#define MCPPROVIDER_INCLUDED

#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h>

namespace Edmund {
  namespace Hardware {
    class McpProvider {
      Adafruit_MCP23017* currentMcp;
      TwoWire* wire;
      bool ready = false;
    public:
      McpProvider() : currentMcp{ new Adafruit_MCP23017() }, wire{ new TwoWire() }  {  }

      ~McpProvider() {
        delete (currentMcp);
        delete (wire);
      }

      void Initialize(byte SDA, byte SDB);
      bool IsReady() const;
      void pinMode(byte pin, byte mode);
      void setupInterruptPinMode(byte pin, byte mode, byte interupt_mode);
      int digitalRead(byte pin);

      uint16_t GetRegisters() {
        if (!ready) return 0;
        return currentMcp->readGPIOAB();
      }
    };
  }
}
#endif