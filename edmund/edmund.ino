#include <Adafruit_MCP23017.h>

#include "./edmund.h"

Edmund::EntryPoint ep;

void setup() {
  ep.setup();
  }

void loop() {  
  ep.loop();
 }
