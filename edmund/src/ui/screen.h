#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "../hardware/device.h"
#include "../game.h"

namespace Edmund {
  namespace UI {
    enum ScreenEnum {
      MainScreenEnum = 1,
      ConfigScreenEnum = 2,
      BootScreenEnum = 3
    };

    class IScreen
    {
      public:
        virtual ScreenEnum loop(Device& hardware, Game& game) = 0;
    };
  }
}

#endif
