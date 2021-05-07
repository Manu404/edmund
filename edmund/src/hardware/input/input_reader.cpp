 #include "./input_reader.h"

namespace Edmund {
  namespace Hardware {

    void ESP82666DigitalInputReader::Initialize(){
      pinMode(pin, INPUT);
    }
    void ESP82666DigitalInputReader::readState() { 
      state = digitalRead(pin);
    }
    
    void MCPDigitalInputReader::Initialize(){
      mcpProvider->pinMode(pin, INPUT);
    }    

    void MCPDigitalInputReader::readState() { 
      state = mcpProvider->digitalRead(pin);
    }    

    void ESP82666AnalogInputReader::Initialize(){
      pinMode(pin, INPUT_PULLUP);
    }    
    void ESP82666AnalogInputReader::readState() { 
      state = analogRead(pin);
    }

  }
}