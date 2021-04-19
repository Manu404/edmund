#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"

namespace Edmund {
  namespace UI {
    using namespace Edmund::Hardware;

    enum ScreenEnum {
      MainScreenEnum = 1,
      ConfigScreenEnum = 2,
      BootScreenEnum = 3
    };

    class IScreen
    {
      public:
        virtual ScreenEnum loop(Edmund::Hardware::Device& hardware, Game& game) = 0;
    };
  }
}

#endif
