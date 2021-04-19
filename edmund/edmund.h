#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./src/hardware/hardware.h"
#include "./src/game.h"
#include "./src/ui/screenmanager.h"

class Edmund {
  private:
    int debug = -1;
    Game* game = new Game();
    Hardware* hardware = new Hardware();
    UI::ScreenManager* screenManager = new UI::ScreenManager();
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
#endif
