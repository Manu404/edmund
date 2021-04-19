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
    Hardware* hardware = new Hardware();
    Edmund::UI::ScreenManager* screenManager = new Edmund::UI::ScreenManager();
  public:
    void loop()
    {
      hardware->BeginFrame();
      screenManager->loopCurrent(*hardware, *game);
      hardware->EndFrame();

      if (hardware->IsResetPressed() == 1)
        game->Reset();
    }

    void setup()
    {
      hardware->Initialize();
      game->LoadGameState(hardware->LoadStateFromSpiff());
    }
  };
}
#endif
