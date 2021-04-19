#ifndef SCREENMA_INCLUDED
#define SCREENMA_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"
#include "screen.h"

namespace Edmund {
  namespace UI {
    using namespace Edmund::Hardware;

    class ScreenManager {
      public:
        ScreenManager();
        void loopCurrent(Device& hardware, Game& game);
        void NavigateTo(ScreenEnum screen);
      private:
        IScreen* current;
    };
  }
}
#endif
