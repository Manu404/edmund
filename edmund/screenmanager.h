#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "hardware.h"
#include "game.h"
#include "screen.h"



class ScreenManager
{
  public:
    ScreenManager();
    void loopCurrent(Hardware& hardware, Game& game);
    void NavigateTo(ScreenEnum screen);
  private:
    IScreen* current;
};
#endif
