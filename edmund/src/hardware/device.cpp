#include "./device.h"

extern "C" {
  #include "user_interface.h"
}
extern "C" {
  #include "gpio.h"
}

void wakeup(void) {
  Serial.print("#");
}

namespace Edmund {
    // CE = D0, DC = D1, CLK = D2, DIN = D3, RST = D4
    Device::Device() :LcdProvider(new Adafruit_PCD8544(D2, D3, D1, D0, D4)),
      InputProvider(new McpProvider(), PinMapping()),
      stateArray{ new ESPFlash<GameState>("/currentGame") }{
    }

    Device::Device(Adafruit_PCD8544* _lcd, McpProvider* _mcp, ESPFlash<GameState>* _stateArray, PinMapping _mapping) :
      LcdProvider(new Adafruit_PCD8544(D2, D3, D1, D0, D4)),
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

      this->InputProvider::beginFrame();
      this->LcdProvider::beginFrame();
    }

    void Device::EndFrame() {
      this->InputProvider::endFrame();
      this->LcdProvider::endFrame();

      WaitRemainingFrameTime();
      EnsureSleep();
    }

    void Device::WaitRemainingFrameTime() {
      frameDuration = millis() - frameStart;
      if (frameDuration < FRAME_DURATION_MS)
        delay(FRAME_DURATION_MS - frameDuration);
    }

    void Device::EnsureSleep() {
      if (getInputStatus() == INPUT_Active || rotaryInterruptTriggered == true)
      {
        sleepTick = 0;
        rotaryInterruptTriggered = false;
      }
      else
        sleepTick += 1;

      if (sleepTick > SLEEP_TICK_LIMIT) {
        Serial.print("z");
        startLightSleep();
      }
      else
        Serial.print("+");
    }

    void Device::SaveStateToSpiff(const GameState& state) {
      stateArray->set(state);
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