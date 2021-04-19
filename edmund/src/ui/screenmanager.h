#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"
#include "screen.h"

namespace UI {
  class ScreenManager {
    public:
      ScreenManager();
      void loopCurrent(Hardware& hardware, Game& game);
      void NavigateTo(ScreenEnum screen);
    private:
      IScreen* current;
  };
}
#endif
