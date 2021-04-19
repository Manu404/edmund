#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "screen.h"

namespace Edmund {
  using namespace UI;
  class ScreenManager {
    public:
      ScreenManager();
      void LoopCurrent(Device& hardware, Game& game);
      void NavigateTo(ScreenEnum screen);
      void RegisterInstance(IScreen* screen);
    private:
      IScreen* current;
      IScreen* screens[4];
  };
}
#endif
