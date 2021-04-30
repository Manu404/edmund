#ifndef CONFIGSCREEN_INCLUDED
#define CONFIGSCREEN_INCLUDED

#include "screen.h"

namespace Edmund {
  namespace UI {
    class ConfigScreen : public IScreen
    {
      public:
        ConfigScreen() : IScreen() { }

        virtual ScreenEnum loop(const Device& hardware, Game& game)
        {
          hardware.Print("L to reset", 7, 7);          
          
          if (hardware.IsLeftPressed())
            game.Reset();

          if (hardware.IsMiddlePressed() == 1)
            return BootScreenEnum;

          return GetNavigationId();
        }

        virtual void processInputs(const Device& hardware, Game& game) { }

        virtual const ScreenEnum GetNavigationId() const { return ConfigScreenEnum; }
    };
  }
}
#endif
