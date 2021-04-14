#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "game.h"
#include "hardware.h"

enum ScreenEnum {
  MainScreenEnum = 1,
  ConfigScreenEnum = 2,
  BootScreenEnum = 3
};

class IScreen
{
  public: 
    virtual ScreenEnum loop(Hardware& hardware, Game& game) = 0;
};


#endif
