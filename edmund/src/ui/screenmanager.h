#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "screen.h"

namespace Edmund {
  using namespace UI;
  class ScreenManager {
    public:
      ScreenManager();
      void loopCurrent(Device& hardware, Game& game);
      void NavigateTo(ScreenEnum screen);
    private:
      IScreen* current;
  };
}
#endif
