#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "screen.h"

namespace Edmund {
  namespace UI {
    using namespace Edmund::Hardware;

    class ConfigScreen : public IScreen
    {
      private:
        int debug = -1;
      public:
        ConfigScreen() { }
        virtual ScreenEnum loop(Device& hardware, Game& game)
        {
          //if (hardware.IsDebugPressed() == 1);

          if (hardware.IsMiddlePressed() == 1)
            return BootScreenEnum;
          return ConfigScreenEnum;
        }
    };
  }
}

#endif
