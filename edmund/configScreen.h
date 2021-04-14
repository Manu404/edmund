#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "hardware.h"
#include "game.h"
#include "screen.h"

class ConfigScreen : public IScreen
{
  private:
    int debug = -1; 
    
  public: 
    ConfigScreen(){
      
    }
    virtual ScreenEnum loop(Hardware& hardware, Game& game)
    {
      hardware.PrintLine("Config");
      
      if(hardware.IsMiddlePressed() == 1)
        return BootScreenEnum;
      return ConfigScreenEnum;
    } 
};

#endif
