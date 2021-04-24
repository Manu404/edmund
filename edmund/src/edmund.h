#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./hardware/device.h"
#include "./ui/screen_manager.h"
#include "./game.h"
#include <ESP8266WiFi.h>

int needReset = 0;

 extern "C" {
   #include "user_interface.h"
 }
 extern "C" {
   #include "gpio.h"
 }

void wakeup(void) {
  needReset = 1;
  Serial.println("-");
}

void light_sleep(){
  //wifi_station_disconnect(); //not needed
  uint32_t sleep_time_in_ms = 2000;
  wifi_set_opmode(NULL_MODE);
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  gpio_pin_wakeup_enable(GPIO_ID_PIN(D7), GPIO_PIN_INTR_LOLEVEL);
  wifi_fpm_set_wakeup_cb(wakeup);
  wifi_fpm_do_sleep(sleep_time_in_ms * 1000);
  delay(sleep_time_in_ms + 1);
 }

namespace Edmund {
  class EntryPoint {
  private:
    int debug = -1;
    Game* game = new Game();
    Device* device = new Device();
    ScreenManager* screenManager = new ScreenManager();
    int lastFrameDuration, lastFrame, currentFrame;

  public:

    void loop() {
      if (needReset == 1) {
        device->Initialize();
        game->LoadGameState(device->LoadStateFromSpiff());
        screenManager->NavigateTo(HomeMenuScreenEnum);
        needReset = 0;
      }
      device->BeginFrame();
      screenManager->LoopCurrent(*device, *game);
      game->RefreshEllapsedTime();
      if (debug)
        displayDebug(device);
      device->EndFrame();

      if (device->IsResetPressed() == 1)
        game->Reset();

      Serial.println("+");

      light_sleep();
    }

    void setup() {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiff());
      screenManager->NavigateTo(HomeMenuScreenEnum);
      WiFi.mode(WIFI_STA);
      pinMode(D8, INPUT);
      Serial.print("setup done");
    }

    void displayDebug(Device* hardware) {
      if (!hardware) return;
      currentFrame = millis();
      lastFrameDuration = currentFrame - lastFrame;
      lastFrame = currentFrame;
      hardware->DrawBox(0, 0, 20, 6, BLACK);
      hardware->PrintNumberSmall(0, 0, lastFrameDuration, WHITE, 3);
      hardware->PrintNumberSmall(10, 0, round(1000 / (lastFrameDuration != 0 ? lastFrameDuration : 1)), WHITE, 3);
    }
  };
}
#endif
