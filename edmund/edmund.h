#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./src/hardware/device.h"
#include "./src/ui/screenmanager.h"
#include "./src/game.h"

namespace Edmund {
  class EntryPoint {
  private:
    int debug = -1;
    Game* game = new Game();
    Device* device = new Device();
    ScreenManager* screenManager = new ScreenManager();
  public:

    void loop() {
      device->BeginFrame();
      screenManager->LoopCurrent(*device, *game);
      game->RefreshEllapsedTime();
      device->EndFrame();

      if (device->IsResetPressed() == 1)
        game->Reset();
    }

    void setup() {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiff());
    }
  };
}
#endif
