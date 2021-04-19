#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./src/hardware/hardware.h"
#include "./src/game.h"
#include "./src/ui/screenmanager.h"

namespace Edmund {
  class EntryPoint {
  private:
    int debug = -1;
    Game* game = new Game();
    Edmund::Hardware::Device* device = new Edmund::Hardware::Device();
    Edmund::UI::ScreenManager* screenManager = new Edmund::UI::ScreenManager();
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
