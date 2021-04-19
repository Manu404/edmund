#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "screen.h"

namespace Edmund {
  namespace UI {
    class ConfigScreen : public IScreen
    {
      private:
        int debug = -1;
      public:
        ConfigScreen() : IScreen(1) { }
        virtual ScreenEnum loop(Device& hardware, Game& game)
        {
          //if (hardware.IsDebugPressed() == 1);

          if (hardware.IsMiddlePressed() == 1)
            return BootScreenEnum;
          return GetNavigationId();
        }
        virtual void updateNavigationPosition(int position) {

        }

        virtual ScreenEnum GetNavigationId() { return ConfigScreenEnum; }
    };
  }
}

#endif
