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
        ConfigScreen() : IScreen() { }

        virtual ScreenEnum loop(Device& hardware, Game& game)
        {
          if (hardware.IsMiddlePressed() == 1)
            return BootScreenEnum;
          return GetNavigationId();
        }

        virtual void processInputs(Device& hardware, Game& game) { ; }

        virtual ScreenEnum GetNavigationId() { return ConfigScreenEnum; }
    };
  }
}
#endif
