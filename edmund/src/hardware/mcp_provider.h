#pragma once
#ifndef MCPPROVIDER_INCLUDED
#define MCPPROVIDER_INCLUDED

#include <Adafruit_MCP23017.h>
#include <Wire.h>

class McpProvider {
  Adafruit_MCP23017* current_mcp;
  TwoWire* wire;
  int ready = 0;
public:
  McpProvider() : current_mcp{ new Adafruit_MCP23017() }, wire{ new TwoWire() }  {  }

  void Initialize(uint SDA, uint SDC) {
    Serial.println(String(SDA) + " - " + String(SDC));
    wire->begin(SDA, SDC);
    current_mcp->begin(wire);
    current_mcp->setupInterrupts(true, false, LOW);
    ready = 1;
  }

  int IsReady() {
    return ready;
  }

  void pinMode(int pin, int mode) {
    current_mcp->pinMode(pin, mode);
  }
  void setupInterruptPinMode(uint pin, int mode, int interupt_mode) {
    current_mcp->pinMode(pin, mode);
    current_mcp->pinMode(pin, interupt_mode);
  }
  int digitalRead(int pin) {
    return current_mcp->digitalRead(pin);
  }
};
#endif