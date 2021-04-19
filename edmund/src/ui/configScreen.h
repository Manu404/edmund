#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "../hardware/hardware.h"
#include "../game.h"
#include "screen.h"

namespace UI {
  class ConfigScreen : public IScreen
  {
    private:
      int debug = -1;

    public:
      ConfigScreen() {


      }
      virtual ScreenEnum loop(Hardware& hardware, Game& game)
      {
        //if (hardware.IsDebugPressed() == 1);

        if (hardware.IsMiddlePressed() == 1)
          return BootScreenEnum;
        return ConfigScreenEnum;
      }
  };
}

#endif
