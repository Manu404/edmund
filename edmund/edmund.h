#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./src/hardware/hardware.h"
#include "./src/ui/screenmanager.h"
#include "./src/game.h"

namespace Edmund {
  class EntryPoint {
  private:
    int debug = -1;
    Game* game = new Game();
    Hardware::Device* device = new Hardware::Device();
    UI::ScreenManager* screenManager = new UI::ScreenManager();
  public:
    void loop()
    {
      device->BeginFrame();
      screenManager->loopCurrent(*device, *game);
      device->EndFrame();

      if (device->IsResetPressed() == 1)
        game->Reset();
    }

    void setup()
    {
      device->Initialize();
      game->LoadGameState(device->LoadStateFromSpiff());
    }
  };
}
#endif
