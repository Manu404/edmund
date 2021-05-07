#pragma once
#ifndef INNPUTREADER_INCLUDED
#define INNPUTREADER_INCLUDED

#include "Arduino.h"
#include <memory>
#include "mcp_provider.h"
#include "input_api.h"

namespace Edmund {
  namespace Hardware {

    class ESP82666DigitalInputReader : public IInputReader<byte> {
      private:
        byte pin;
      public:
        ESP82666DigitalInputReader(byte _pin) : pin(_pin) { }
        void Initialize();
      protected:
        void readState();
    };

    class MCPDigitalInputReader : public IInputReader<byte> {
      private:
        std::shared_ptr<McpProvider> mcpProvider;
        byte pin;
      public:
        MCPDigitalInputReader(byte _pin, std::shared_ptr<McpProvider> _mcpProvider) : mcpProvider(_mcpProvider) { }        
        void Initialize();
      protected:
        void readState();
    };

    class ESP82666AnalogInputReader : public IInputReader<float> {
      private:
        byte pin;
      public:
        ESP82666AnalogInputReader(byte _pin) : pin(_pin) { }        
        void Initialize();
      protected:
        void readState();
    };

  }
}
#endif