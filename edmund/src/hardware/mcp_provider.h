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
      void Initialize(uint SDA, uint SDC);
      int IsReady();
      void pinMode(int pin, int mode);
      void setupInterruptPinMode(uint pin, int mode, int interupt_mode);
      int digitalRead(int pin);
    };
  }
}
#endif