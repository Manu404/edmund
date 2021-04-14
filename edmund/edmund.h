#ifndef EDMUND_INCLUDED
#define EDMUND_INCLUDED

#include "./hardware.h"
#include "./game.h"
#include "./screenmanager.h"

class Edmund {
  private:
    int debug = -1;
    Game game = Game();
    Hardware hardware = Hardware();
    ScreenManager screenManager = ScreenManager();

  public:
    void loop()
    {
      hardware.BeginFrame();
      screenManager.loopCurrent(hardware, game); 
    
      /*else {
      }  */
      hardware.EndFrame();
      
      if(hardware.IsResetPressed() == 1)
        game = Game();
    }   
    
    void setup()
    {
      hardware.Initialize();
      game.state = hardware.LoadStateFromSpiff();
    }
};
#endif
