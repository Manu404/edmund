#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./hardware/device.h"
#include "./ui/screen_manager.h"
#include "./game.h"

namespace Edmund {
  class EntryPoint {
  private:
    int debug = -1;
    Game* game = new Game();
    Device* device = new Device();
    ScreenManager* screenManager = new ScreenManager();
    unsigned long lastFrameDuration = 0, lastFrame = 0, currentFrame = 0;

  public:

    void loop() {
      device->BeginFrame();
      
      screenManager->LoopCurrent(*device, *game);
      game->RefreshEllapsedTime();
      
      if (debug == 1)
        displayDebug(device);
      
      if (device->IsResetPressed() == 1)
        game->Reset();

      device->EndFrame();
    }

    void setup() {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiff());
      screenManager->NavigateTo(HomeMenuScreenEnum);
      Serial.println("setup");
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
