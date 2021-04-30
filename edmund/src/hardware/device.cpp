#include "./device.h"

void wakeup(void) {
  Serial.print("#");
}

namespace Edmund {
    // CE = D0, DC = D1, CLK = D2, DIN = D3, RST = D4
    Device::Device() : LcdProvider(std::unique_ptr<Adafruit_PCD8544>(new Adafruit_PCD8544(D2, D3, D1, D0, D4))),
                       InputProvider(std::unique_ptr<McpProvider>(new McpProvider()), PinMapping()),
                       stateArray{ new ESPFlash<GameState>("/currentGame") }
    { }

    Device::Device(std::unique_ptr<Adafruit_PCD8544> _lcd, std::unique_ptr<McpProvider> _mcp, ESPFlash<GameState>* _stateArray, PinMapping _mapping) :
      LcdProvider(std::move(_lcd)),
      InputProvider(std::move(_mcp), _mapping),    
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

      this->InputProvider::beginFrame();
      this->LcdProvider::beginFrame();
    }

    void Device::EndFrame(const GameState& game) {
      this->InputProvider::endFrame();
      this->LcdProvider::endFrame();

      waitRemainingFrameTime();
      ensureSleep(game);
    }

    void Device::waitRemainingFrameTime() {
      frameDuration = millis() - frameStart;
      if (frameDuration < FRAME_DURATION_MS)
        delay(FRAME_DURATION_MS - frameDuration);
    }

    void Device::ensureSleep(const GameState& game) {
      if (getInputStatus() == INPUT_Active || rotaryInterruptTriggered == true)
      {
        sleepTick = 0;
        rotaryInterruptTriggered = false;
        sleeping = false;
      }
      else
        sleepTick += 1;

      if (sleepTick > SLEEP_TICK_LIMIT) {
        if (!sleeping)
        {
          SaveStateToSpiff(game);
          Serial.println("save");
        }
        sleeping = true;
        Serial.print("z");
        startLightSleep();
      }
      else
        Serial.print("+");
    }

    void Device::SaveStateToSpiff(const GameState& game) {
      stateArray->set(game);
    }

    GameState Device::LoadStateFromSpiff() {
      return stateArray->get();
    }

    void Device::startLightSleep() {
      uint32_t sleep_time_in_ms = SLEEP_TIME;
      wifi_set_opmode(NULL_MODE);
      wifi_set_sleep_type(LIGHT_SLEEP_T);
      wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
      wifi_fpm_open();
      wifi_fpm_set_wakeup_cb(wakeup);
      wifi_fpm_do_sleep(sleep_time_in_ms * 1000);
      delay(sleep_time_in_ms + 1);
    }
}