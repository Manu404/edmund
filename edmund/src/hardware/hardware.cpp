#include "./hardware.h"

namespace Edmund {
  namespace Hardware {
    Device::Device() :LcdProvider(new Adafruit_PCD8544(D0, D1, D3, D4, D2)),
      InputProvider(new McpProvider(), PinMapping()),
      stateArray{ new ESPFlash<GameState>("/currentGame") }{
    }

    Device::Device(Adafruit_PCD8544* _lcd, McpProvider* _mcp, ESPFlash<GameState>* _stateArray, PinMapping _mapping) :
      LcdProvider(new Adafruit_PCD8544(D0, D1, D3, D4, D2)),
      InputProvider(_mcp, _mapping),
      stateArray(_stateArray) {
    }

    void Device::Initialize() {
      Serial.begin(SERIAL_SPEED);
      Serial.println("init.");
      initScreen();
      initInputs();
    }

    void Device::BeginFrame() {
      frameStart = millis();
      clear();
    }

    void Device::EndFrame() {
      display();
      frameDuration = (millis() - frameStart);
      if (frameDuration < FRAME_DURATION_MS)
        delay(FRAME_DURATION_MS - frameDuration);
      refreshInputs();
    }

    void Device::SaveStateToSpiff(const GameState& state) {
      stateArray->set(state);
    }

    GameState Device::LoadStateFromSpiff() {
      return stateArray->get();
    }
  }
}