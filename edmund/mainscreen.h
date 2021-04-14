#ifndef MAINSCREEN_INCLUDED
#define MAINSCREEN_INCLUDED

#include "hardware.h"
#include "game.h"
#include "screen.h"

class Mainscreen : public IScreen
{
  private:
    int debug = -1; 
    
  public: 
    Mainscreen(){
      
    }
    virtual ScreenEnum loop(Hardware& hardware, Game& game)
    {
      if(hardware.HasPotChanged())
        game.UpdateCurrentPropertyFromPot(hardware.GetPositionFromPot(3 * 3));
        
      if(hardware.IsRightPressed() == 1)
        game.UpdateCurrentProperty(1);    
      if(hardware.IsLeftPressed() == 1)
        game.UpdateCurrentProperty(-1);
      if(hardware.IsRightPressed() == 1 || hardware.IsLeftPressed())
        hardware.SaveStateToSpiff(game.state);    
        
      if(hardware.IsDebugPressed() == 1)
        debug *= -1;
             
      hardware.PrintLine(game.GetOpponentLifeLine());
      hardware.PrintLine(game.GetCommanderDamages());
      hardware.PrintLine(game.GetReceivedCommanderDamages());
      
      if(debug == 1) {    
        hardware.PrintLine(hardware.GetDebugLine());
        hardware.PrintLine(game.GetCurrentPosition());
      }
      
      if(hardware.IsMiddlePressed() == 1)
        return ConfigScreenEnum;
      return MainScreenEnum;
    } 
};

#endif
