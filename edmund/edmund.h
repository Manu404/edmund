#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./src/hardware/device.h"
#include "./src/ui/screenmanager.h"
#include "./src/game.h"

namespace Edmund {
  class EntryPoint {
  private:
    int debug = 1;
    Game* game = new Game();
    Device* device = new Device();
    ScreenManager* screenManager = new ScreenManager();


    int lastFrameDuration, lastFrame, currentFrame;

  public:

    void loop() {
      device->BeginFrame();
      screenManager->LoopCurrent(*device, *game);
      game->RefreshEllapsedTime();
      if (debug)
        displayDebug(device);
      device->EndFrame();

      if (device->IsResetPressed() == 1)
        game->Reset();
    }

    void setup() {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiff());
      screenManager->NavigateTo(HomeMenuScreenEnum);
    }

    void displayDebug(Device* hardware) {
      if (!hardware) return;
      currentFrame = millis();
      lastFrameDuration = currentFrame - lastFrame;
      lastFrame = currentFrame;
      hardware->DrawBox(0, 0, 20, 6, BLACK);
      hardware->PrintNumberSmall(0, 0, lastFrameDuration, WHITE, 3);
      hardware->PrintNumberSmall(10, 0, round(1000 / lastFrameDuration), WHITE, 3);
    }
  };
}
#endif
